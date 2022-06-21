<?php

use App\Models\Algo;
use Illuminate\Support\Facades\Route;

Route::view('/', 'app');

Route::get('/seed', function () {
    Algo::create([
        'name' => 'FIFO'
    ]);

    Algo::create([
        'name' => 'SJF'
    ]);

    Algo::create([
        'name' => 'Round Robin'
    ]);

    Algo::create([
        'name' => 'Priority - NP'
    ]);

    dd('success');
});
