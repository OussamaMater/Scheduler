<?php

namespace App\Http\Livewire;

use App\Models\History;
use Livewire\Component;
use Illuminate\Support\Facades\DB;

class LastExecutions extends Component
{
    protected $listeners = ['updated_history' => 'render'];

    public function clearHistory()
    {
        DB::table('histories')->delete();
        $this->emit('updated_history');
    }

    public function render()
    {
        return view('livewire.last-executions', [
            'executions' => History::latest()->get(),
        ]);
    }
}
