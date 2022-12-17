project('dross', 'cpp')
sfml_dep = dependency('sfml-graphics')
inc = include_directories('inc')
src_files = [
    'src/Display.cpp',
    'src/Enemy.cpp',
    'src/Game.cpp',
    'src/Level.cpp',
    'src/NP_Entity.cpp',
    'src/Player.cpp',
    'src/Projectile.cpp',
    'src/main.cpp'
]

flags = []
if get_option('data_dir') != ''
    flags += '-DDATA_DIR="' + get_option('data_dir') + '"'
elif get_option('test')
    flags += '-DDATA_DIR="' + meson.source_root() + '"'
endif

message(flags)

if get_option('all_levels')
    flags += '-DALL_LEVELS'
endif

if get_option('hit_box')
    flags += '-DHIT_BOX'
endif

executable( meson.project_name(), 
            src_files,
            include_directories: inc,
            dependencies : sfml_dep,
            cpp_args : flags
            )