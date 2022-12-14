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

executable( meson.project_name(), 
            src_files,
            include_directories: inc,
            dependencies : sfml_dep,
            )