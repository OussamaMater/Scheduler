<!DOCTYPE html>
<html lang="en">

<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>Scheduler - WebInterface</title>
    <link type="text/css" href="{{ asset('css/volt.css') }}" rel="stylesheet">

    @livewireStyles
</head>

<body>
    @livewire('gantt-diagram')
    <div class="row mx-4 mb-4">
        @livewire('last-executions')
        @livewire('most-executed')
    </div>

    <footer class="mx-4 mb-4 bg-white rounded shadow p-2">
        <p class="text-center mt-3">Scheduler - Made with ❤️ by <strong>Mater Oussama</strong></p>
    </footer>

    <!-- Core -->
    <script src="{{ asset('js/@popperjs/core/dist/umd/popper.min.js') }}"></script>
    <script src="{{ asset('js/bootstrap/dist/js/bootstrap.min.js') }}"></script>

    <script src="{{ asset('js/volt.js') }}"></script>

    @livewireScripts

</body>

</html>
