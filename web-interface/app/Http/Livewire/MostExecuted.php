<?php

namespace App\Http\Livewire;

use App\Models\Algo;
use App\Models\History;
use Livewire\Component;

class MostExecuted extends Component
{
    protected $listeners = ['updated_history' => 'render'];

    public function render()
    {
        $total        = History::count();
        $algos        = Algo::all();
        $mostExecuted = [];

        foreach ($algos as $algo) {
            $mostExecuted[] = [
                $algo->name,
                $total != 0 ? round((History::whereName($algo->name)->count() * 100) / $total, 2) : 0
            ];
        }

        usort($mostExecuted, function ($a, $b) {
            return $b[1] <=> $a[1];
        });


        return view('livewire.most-executed', [
            'mostExecuted' => $mostExecuted,
        ]);
    }
}
