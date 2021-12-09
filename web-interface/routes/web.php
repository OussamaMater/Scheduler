<?php

use mikehaertl\shellcommand\Command;
use Illuminate\Support\Facades\Route;


// El output mtei CLI nformatih kima nheb
// El output li jey ll php ykoun 3ibara ala 3 files, w ken haka nbadil directory mtehom bsh yab9a
// C ndhif, naaml wahda feha l order, wahda feha l finish time, wahda feha l arival, priority, burst, etc..
// namelhom 3ibara ala helpers fil C

// ken haka nkhali el main mte kol algo ala wahdo ll php, fiblast yetaada b atwel haja
// ena maw l ing? ena li nhel l machekel? hedhi ahsen solution ;)

// ! maybe naaml unit test l C w nhothom fi rapport
// nwali ken haka nshouf kifeh nzidha fazet y selection l fichier
Route::view('/', 'app');

Route::get('/test', function () {
    // this will be game changing
    // $command = new Command('ls /home/oussama/Desktop/Code/scheduler/c-program/algos/config.txt');
    // if ($command->execute()) {
    //     echo $command->getOutput();
    // } else {
    //     dump(empty($command->getError()));
    // }
    dump(config('path.name'));
    //config(['path.name' => 'America/Chicago']);
    dump(config('path.name'));
    dd('done');
});
