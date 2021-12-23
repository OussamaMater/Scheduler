<div class="col-12 col-md-6 mb-4">
    <div class="card border-0 shadow">
        <div class="card-header">
            <div class="row align-items-center">
                <div class="col-10">
                    <h2 class="fs-5 fw-bold mb-0">Recent Executions</h2>
                </div>
                <div class="col-2">
                    @if (\App\Models\History::count() > 0)
                        <svg xmlns="http://www.w3.org/2000/svg" class="icon icon-sm text-danger float-end" fill="none"
                            viewBox="0 0 24 24" stroke="currentColor" style="cursor: pointer" wire:click="clearHistory">
                            <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                                d="M19 7l-.867 12.142A2 2 0 0116.138 21H7.862a2 2 0 01-1.995-1.858L5 7m5 4v6m4-6v6m1-10V4a1 1 0 00-1-1h-4a1 1 0 00-1 1v3M4 7h16" />
                        </svg>
                    @endif
                </div>
            </div>
        </div>
        <div class="table-responsive">
            <table class="table align-items-center table-flush">
                <thead class="thead-light">
                    <tr>
                        <th class="border-bottom" scope="col">Algorithm</th>
                        <th class="border-bottom" scope="col">Turn Around Time</th>
                        <th class="border-bottom" scope="col">Waiting Time</th>
                        <th class="border-bottom" scope="col">Executed At</th>
                    </tr>
                </thead>
                <tbody>
                    @forelse ($executions->take(5) as $executed)
                        <tr>
                            <th class="text-gray-900" scope="row">{{ $executed->name }}</th>
                            <td class="fw-bolder text-gray-500">{{ $executed->turn_around_avg }}</td>
                            <td class="fw-bolder text-gray-500">{{ $executed->waiting_average }}</td>
                            <td class="fw-bolder text-gray-500">{{ $executed->created_at->diffForHumans() }}</td>
                        </tr>
                    @empty
                        <td class="text-center" colspan="4">
                            <h3 class="my-4"><em>No Executions Were Saved</em></h3>
                        </td>
                    @endforelse
                </tbody>
            </table>
        </div>
    </div>
</div>
