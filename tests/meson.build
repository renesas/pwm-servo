unity_dep = dependency('Unity')
unity_proj = subproject('unity')

include_dir_list = [base_include_dirs, 'data', 'mocks']

servo_dep = declare_dependency(
    include_directories: [base_include_dirs],
    link_with: servo_lib,
)

timer_spy_code = ['mocks/timer_spy.c']
timer_spy_test_code = [
    'mocks/test_timer_spy.c',
    'runners/test_timer_spy_runner.c',
]

timer_spy_exe = executable(
    'timer-spy-test',
    sources: [timer_spy_code, timer_spy_test_code],
    include_directories: include_dir_list,
    dependencies: [unity_dep, servo_dep],
)

servo_test_exe = executable(
    'servo-test',
    sources: [
        timer_spy_code,
        'test_servo.c',
        'test_servo_parameter_checking.c',
        'runners/test_servo_runner.c',
        'data/test_servo_shared.c',
    ],
    include_directories: include_dir_list,
    dependencies: [unity_dep, servo_dep],
)

test('Timer Spy Test', timer_spy_exe)
test('Timer Spy Test', servo_test_exe)
