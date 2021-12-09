<div class="col-12 col-md-6">
    <div class="card border-0 shadow mb-4">
        <div class="card-header">
            <div class="row align-items-center">
                <div class="col">
                    <h2 class="fs-5 fw-bold mb-0">Most Executed</h2>
                </div>
            </div>
        </div>
        <div class="card-body">
            @foreach ($mostExecuted as $executed)
                <div class="row align-items-center mb-4">
                    <div class="col-auto">
                        <svg class="icon icon-sm text-gray-500" fill="currentColor" viewBox="0 0 20 20"
                            xmlns="http://www.w3.org/2000/svg">
                            <path d="M9 2a1 1 0 000 2h2a1 1 0 100-2H9z"></path>
                            <path fill-rule="evenodd"
                                d="M4 5a2 2 0 012-2 3 3 0 003 3h2a3 3 0 003-3 2 2 0 012 2v11a2 2 0 01-2 2H6a2 2 0 01-2-2V5zm3 4a1 1 0 000 2h.01a1 1 0 100-2H7zm3 0a1 1 0 000 2h3a1 1 0 100-2h-3zm-3 4a1 1 0 100 2h.01a1 1 0 100-2H7zm3 0a1 1 0 100 2h3a1 1 0 100-2h-3z"
                                clip-rule="evenodd"></path>
                        </svg>
                    </div>
                    <div class="col">
                        <div class="progress-wrapper">
                            <div class="progress-info">
                                <div class="h6 mb-0">{{ $executed[0] }}</div>
                                <div class="small fw-bold text-gray-500"><span>{{ $executed[1] }} %</span></div>
                            </div>
                            <div class="progress mb-0">
                                <div class="progress-bar bg-{{ $executed[1] <= 25 ? 'danger' : ($executed[1] <= 50 ? 'secondary' : 'success') }}"
                                    role="progressbar" aria-valuenow="75" aria-valuemin="0" aria-valuemax="100"
                                    style="width: {{ $executed[1] }}%;">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            @endforeach
        </div>
    </div>
</div>
