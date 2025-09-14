shell_src = files('src/main.cpp',
                  'src/applets/applets.cpp',
                  'src/applets/cd.cpp',
                  'src/applets/exit.cpp',
                  'src/applets/ls.cpp')

executable('shell',
           shell_src,
           dependencies: porticxx_dep,
           cpp_args: '-DPCXX_ARCH_X86_64')