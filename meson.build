project(
    'servo',
    ['c'],
    default_options: ['b_sanitize=address,undefined', 'b_lundef=false'],
)

base_include_dirs = include_directories(
    [
        'include',
        'include/ra/fsp/inc/api',
        'src/rm_servo',
        # 'include/ra_cfg/fsp_cfg',
    ],
)

servo_src = ['src/rm_servo/rm_servo.c']

warning_args = [
    '-Wall',
    '-Wextra',
    '-Wconversion',
    '-Wuninitialized',
    '-Wunused',
    '-Wshadow',
    '-Wpointer-arith',
    '-Waggregate-return',
    '-Wmissing-declarations',
    '-Wmissing-prototypes',
    '-Wstrict-prototypes',
    '-Wbad-function-cast',
    '-Wno-parentheses-equality',
    '-Wfloat-equal',
    '-Wdouble-promotion',
]

add_project_arguments(warning_args, language: 'c')

servo_lib = static_library(
    'servo',
    sources: servo_src,
    include_directories: [base_include_dirs],
)

subdir('tests')
