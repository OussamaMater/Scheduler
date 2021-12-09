<?php

namespace App\Http\Livewire;

use App\Models\History;
use Livewire\Component;

class LastExecutions extends Component
{
    protected $listeners = ['updated_history' => 'render'];

    public function render()
    {
        return view('livewire.last-executions', [
            'executions' => History::latest()->get(),
        ]);
    }
}
