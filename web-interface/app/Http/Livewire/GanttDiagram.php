<?php

namespace App\Http\Livewire;

use App\Models\Algo;
use App\Models\History;
use Livewire\Component;
use Illuminate\Support\Str;

class GanttDiagram extends Component
{
    public $schedulingAlgorithm = '1';
    public $turnAroundTime      = 0;
    public $waitingTime         = 0;
    public $saveToDataBase      = false;
    public $processesOrder      = [];
    public $processesInfos      = [];
    public $quantum;
    public $output;
    public $axis;

    public function process()
    {
        if ($this->schedulingAlgorithm == 3 && $this->quantum < 1) {
            return $this->dispatchBrowserEvent('alert');
        }

        $this->executeC();
        $this->getProcessesInfos();
        $this->processesOrder = $this->getProcessesOrder();
        $this->axis           = $this->getGanttTimeAxis();
        $this->processesInfos = $this->getProcessesInfos();
        $this->calculateTurnAroundTime();
        $this->calculateWaitingTime();
        if ($this->saveToDataBase) {
            History::create([
                'name'            => Algo::find($this->schedulingAlgorithm)->name,
                'turn_around_avg' => $this->turnAroundTime,
                'waiting_average' => $this->waitingTime,
            ]);
            $this->emit('updated_history');
        }

        $this->dispatchBrowserEvent('animate');
    }

    public function executeC()
    {
        $algo = match ($this->schedulingAlgorithm) {
            '1' => 'fifo',
            '2' => 'sjf',
            '3' => 'rr',
            '4' => 'srt',
            '5' => 'pnp',
        };

        $command = env('BINARY') . ' ' .  env('KEY') . ' ' . env('CONFIG_FILE_PATH') . ' ' .  $algo . ' ' . $this->quantum ?? '' . ' 2>&1';
        exec($command . '', $output);
        return $this->output = $output;
    }

    public function getProcessesOrder()
    {
        $processesOrder = $this->output[0];
        $processesOrder = Str::of($processesOrder)->explode('|');
        $processesOrder->pop();
        return $processesOrder;
    }

    public function getGanttTimeAxis()
    {
        $axis = $this->output[2];
        $axis = Str::of($axis)->explode(' ');
        return $axis;
    }

    public function getProcessesInfos()
    {
        $processesInfos = [];
        // $data = array_slice($this->output, 0, -3);
        $data = array_slice($this->output, 4);
        foreach ($data as $process) {
            $process = Str::replace(' ', '', $process);
            $process = Str::of($process)->explode(',');
            $processesInfos[] = [
                $process[0],
                $process[1], // started
                $process[2], // finished
                $process[3], // turn around time
                $process[4], // burst time
                $process[5], //waiting time
            ];
        }

        return $processesInfos;
    }

    public function calculateTurnAroundTime()
    {
        $this->reset('turnAroundTime'); // from last executions
        foreach ($this->processesInfos as $process) {
            $this->turnAroundTime = $this->turnAroundTime + $process[3];
        }

        $this->turnAroundTime = round($this->turnAroundTime / count($this->processesInfos), 2);
    }

    public function calculateWaitingTime()
    {
        $this->reset('waitingTime'); // from last executions
        foreach ($this->processesInfos as $process) {
            $this->waitingTime = $this->waitingTime + $process[5];
        }

        $this->waitingTime = round($this->waitingTime / count($this->processesInfos), 2);
    }

    public function render()
    {
        return view('livewire.gantt-diagram', ['algos' => Algo::all()]);
    }
}
