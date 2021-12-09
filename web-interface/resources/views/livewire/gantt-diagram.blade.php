<div class="row m-4">
    <div class="col-12 col-md-9 mb-4">
        <div class="card border-0 shadow">
            <div class="card-header">
                <div class="row align-items-center">
                    <div class="col">
                        <h2 class="fs-5 fw-bold mb-0">Gantt Diagram</h2>
                    </div>
                </div>
            </div>
            <div class="card-body">
                <div class="row align-content-center m-2">
                    @forelse ($processesOrder as $process)
                        <div class="col-2 align-content-center bg-secondary border my-3 border-primary gantt words">
                            <h3 class="text-center">{{ $process == 'P-1' ? '_' : $process }}</h3>
                            <div style="margin-bottom: -40px" class="row">
                                <div class="col-6 text-left p-0">
                                    <p style="margin-left: -5px" class="text-left">{{ $axis[$loop->index] }}</p>
                                </div>
                                @if ($loop->last)
                                    <div class="col-6 text-end p-0">
                                        <p class="text-right">{{ $axis[$loop->index + 1] }}</p>
                                    </div>
                                @endif
                            </div>
                        </div>
                    @empty
                        <h3 class="text-center">
                            <em>Please Pick An Algorithm</em>
                        </h3>
                    @endforelse
                </div>
                @if ($processesInfos)
                    <div class="table-responsive mt-4">
                        <table class="table table-centered table-nowrap mb-0 rounded">
                            <thead class="thead-light">
                                <tr>
                                    <th class="border-0 rounded-start">Process</th>
                                    <th class="border-0">Arrival time</th>
                                    <th class="border-0">Burst Time</th>
                                    <th class="border-0">Finish Time</th>
                                    <th class="border-0">Turn Around Time</th>
                                    <th class="border-0 rounded-end">Waiting Time</th>
                                </tr>
                            </thead>
                            <tbody>
                                @foreach ($processesInfos as $process)
                                    <tr>
                                        <td class="border-0">
                                            <a class="d-flex align-items-center">
                                                <div>
                                                    <span class="h6">{{ $process[0] }}</span>
                                                </div>
                                            </a>
                                        </td>
                                        <td class="border-0 fw-bold">{{ $process[1] }}</td>
                                        <td class="border-0 fw-bold">{{ $process[4] }}</td>
                                        <td class="border-0 fw-bold">{{ $process[2] }}</td>
                                        <td class="border-0 fw-bold">{{ $process[3] }}</td>
                                        <td class="border-0 fw-bold">{{ $process[5] }}</td>
                                    </tr>
                                @endforeach
                            </tbody>
                            <thead class="thead-light">
                                <tr>
                                    <th class="border-0 fw-bold rounded-start text-center" colspan="4">Average</th>
                                    <th class="border-0 fw-bold">{{ $this->turnAroundTime }}</th>
                                    <th class="border-0 fw-bold rounded-end">{{ $this->waitingTime }}</th>
                                </tr>
                            </thead>
                        </table>
                    </div>
                @endif
            </div>
        </div>
    </div>
    <div class="col-12 col-md-3">
        <div class="card border-0 shadow">
            <div class="card-header">
                <div class="row align-items-center">
                    <h2 class="fs-5 fw-bold mb-0">Algorithm Picker</h2>
                </div>
            </div>
            <div class="card-body">
                <div class="row justify-content-center">
                    <div class="col-md-12 mb-4">
                        <div>
                            <label for="algos">Scheduling Algorithm</label>
                            <select wire:model="schedulingAlgorithm" class="form-select" id="algos">
                                @foreach ($algos as $algo)
                                    <option value="{{ $algo->id }}">{{ $algo->name }}</option>
                                @endforeach
                            </select>
                        </div>
                    </div>
                    <div class="col-md-12 mb-3">
                        <div class="form-check form-switch">
                            <input wire:model.defer="saveToDataBase" class="form-check-input" type="checkbox"
                                id="flexSwitchCheckDefault">
                            <label class="form-check-label" for="flexSwitchCheckDefault">
                                Save to database
                            </label>
                        </div>
                    </div>
                    @if ($schedulingAlgorithm == 3)
                        <div class="col-md-12 mb-3">
                            <label for="quantum" class="form-label">Quantum</label>
                            <input wire:model.defer="quantum" type="number" class="form-control" id="quantum"
                                placeholder="e.g. 2">
                        </div>
                    @endif
                </div>
                <button wire:click="process" class="btn btn-gray-800 w-100 mt-2 animate-up-2" type="submit">
                    Execute
                </button>
            </div>
        </div>
    </div>

    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
        integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>

    <script src="//cdn.jsdelivr.net/npm/sweetalert2@11"></script>

    <script>
        $(document).ready(function() {
            console.log("ready");
            window.addEventListener('animate', event => {
                $('.words').each(function(i) {
                    $(this).delay(750 * (i + 1)).fadeIn(3000);
                });
            })
        });

        window.addEventListener('alert', event => {
            Swal.fire({
                icon: 'error',
                title: 'Oops...',
                text: 'Quantum must be at least 1!',
            })
        })
    </script>
</div>
