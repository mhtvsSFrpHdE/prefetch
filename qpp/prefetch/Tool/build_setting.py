from pathlib import Path
from enum import Enum

from build_env import _qt_install_path
from build_env import _qt_translate_path
from build_env import _compiler_install_path

from build_core import verbose_print


class BuildFolderType(Enum):
    Debug = 1
    Release = 2
    Release_Verbose = 3
    Release_Performance = 4
    # Collect release build together
    Pack = 5
    # Create all build folder if not exist
    Prepare = 6


BuildFolderTypeMap = {
    'Debug': BuildFolderType.Debug,
    'Release': BuildFolderType.Release,
    'Release_Verbose': BuildFolderType.Release_Verbose,
    'Release_Performance': BuildFolderType.Release_Performance,
    'Pack': BuildFolderType.Pack,
    'Prepare': BuildFolderType.Prepare
}


# build_folder
_prefetch_source_path = Path('..\\').resolve()
build_folder = {
    BuildFolderType.Debug: _prefetch_source_path.parent.joinpath('build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Debug'),
    BuildFolderType.Release: _prefetch_source_path.parent.joinpath('build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release'),
    BuildFolderType.Release_Verbose: _prefetch_source_path.parent.joinpath('build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release_Verbose'),
    BuildFolderType.Release_Performance: _prefetch_source_path.parent.joinpath('build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release_Performance'),
    # Pack eveything together
    BuildFolderType.Pack: _prefetch_source_path.parent.joinpath('Pack')
}
verbose_print('build_folder')
for key in build_folder:
    verbose_print(str(key) + ': ' + str(build_folder[key]))

# exe
exe = {
    BuildFolderType.Release: build_folder[BuildFolderType.Release].joinpath('release').joinpath('prefetch.exe'),
    BuildFolderType.Release_Verbose: build_folder[BuildFolderType.Release_Verbose].joinpath('release').joinpath('prefetch.exe'),
    BuildFolderType.Release_Performance: build_folder[BuildFolderType.Release_Performance].joinpath('release').joinpath('prefetch.exe')
}
verbose_print('\nexe')
for key in exe:
    verbose_print(str(key) + ': ' + str(exe[key]))

# target_exe
target_exe = {
    BuildFolderType.Release: build_folder[BuildFolderType.Pack].joinpath('prefetch.exe'),
    BuildFolderType.Release_Verbose: build_folder[BuildFolderType.Pack].joinpath('prefetch_verbose.exe'),
    BuildFolderType.Release_Performance: build_folder[BuildFolderType.Pack].joinpath('prefetch_performance.exe')
}
verbose_print('\ntarget_exe')
for key in target_exe:
    verbose_print(str(key) + ': ' + str(target_exe[key]))

# config
config = {
    BuildFolderType.Debug: {
        'prefetch.ini': _prefetch_source_path.joinpath('prefetch.ini')
    }
}
config[BuildFolderType.Release] = config[BuildFolderType.Debug]
verbose_print('\nqt_translate')
for key in config:
    verbose_print(key)
    fileGroup = config[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])

# target_config
target_config = {
    BuildFolderType.Debug: {
        'prefetch.ini': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('prefetch.ini')
    },
    BuildFolderType.Release: {
        'prefetch.ini': build_folder[BuildFolderType.Pack].joinpath('prefetch.ini')
    }
}
verbose_print('\nqt_translate')
for key in target_config:
    verbose_print(key)
    fileGroup = target_config[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])

# qt_translate
qt_translate = {
    BuildFolderType.Debug: {
        'qt_zh_CN': _qt_translate_path.joinpath('qt_zh_CN.qm')
    }
}
qt_translate[BuildFolderType.Release] = qt_translate[BuildFolderType.Debug]
verbose_print('\nqt_translate')
for key in qt_translate:
    verbose_print(key)
    fileGroup = qt_translate[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])

# target_qt_translate
target_qt_translate = {
    BuildFolderType.Debug: {
        'qt_zh_CN': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('translate').joinpath('qt').joinpath('qt_zh_CN.qm')
    },
    BuildFolderType.Release: {
        'qt_zh_CN': build_folder[BuildFolderType.Pack].joinpath('translate').joinpath('qt').joinpath('qt_zh_CN.qm')
    }
}
verbose_print('\ntarget_qt_translate')
for key in target_qt_translate:
    verbose_print(key)
    fileGroup = target_qt_translate[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])


# prefetch_translate
_prefetch_translate_folder = _prefetch_source_path.joinpath('Source').joinpath('Translate').joinpath('File')
prefetch_translate = {
    BuildFolderType.Debug: {
        'prefetch_en_US': _prefetch_translate_folder.joinpath('prefetch_en_US.qm'),
        'prefetch_zh_CN': _prefetch_translate_folder.joinpath('prefetch_zh_CN.qm')
    }
}
prefetch_translate[BuildFolderType.Release] = prefetch_translate[BuildFolderType.Debug]
verbose_print('\nprefetch_translate')
for key in prefetch_translate:
    verbose_print(key)
    fileGroup = prefetch_translate[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])

# target_prefetch_translate
target_prefetch_translate = {
    BuildFolderType.Debug: {
        'prefetch_en_US': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('translate').joinpath('prefetch').joinpath('prefetch_en_US.qm'),
        'prefetch_zh_CN': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('translate').joinpath('prefetch').joinpath('prefetch_zh_CN.qm')
    },
    BuildFolderType.Release: {
        'prefetch_en_US': build_folder[BuildFolderType.Pack].joinpath('translate').joinpath('prefetch').joinpath('prefetch_en_US.qm'),
        'prefetch_zh_CN': build_folder[BuildFolderType.Pack].joinpath('translate').joinpath('prefetch').joinpath('prefetch_zh_CN.qm')
    }
}
verbose_print('\ntarget_prefetch_translate')
for key in target_prefetch_translate:
    verbose_print(key)
    fileGroup = target_prefetch_translate[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])

# qt_dll
qt_dll = {
    BuildFolderType.Debug: {
        'QtCore4.dll': _qt_install_path.joinpath('QtCored4.dll'),
        'QtGui4.dll': _qt_install_path.joinpath('QtGuid4.dll')
    },
    BuildFolderType.Release: {
        'QtCore4.dll': _qt_install_path.joinpath('QtCore4.dll'),
        'QtGui4.dll': _qt_install_path.joinpath('QtGui4.dll')
    }
}
verbose_print('\nqt_dll')
for key in qt_dll:
    verbose_print(key)
    fileGroup = qt_dll[key]
    for file in fileGroup:
        verbose_print(file)

# target_qt_dll
target_qt_dll = {
    BuildFolderType.Debug: {
        'QtCore4.dll': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('QtCored4.dll'),
        'QtGui4.dll': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('QtGuid4.dll')
    },
    BuildFolderType.Release: {
        'QtCore4.dll': build_folder[BuildFolderType.Pack].joinpath('QtCore4.dll'),
        'QtGui4.dll': build_folder[BuildFolderType.Pack].joinpath('QtGui4.dll')
    }
}
verbose_print('\ntarget_qt_dll')
for key in target_qt_dll:
    verbose_print(key)
    fileGroup = target_qt_dll[key]
    for file in fileGroup:
        verbose_print(file)

# compiler_dll
compiler_dll = {
    BuildFolderType.Debug: {
        'libgcc_s_dw2-1.dll': _compiler_install_path.joinpath('libgcc_s_dw2-1.dll'),
        'libstdc++-6.dll': _compiler_install_path.joinpath('libstdc++-6.dll'),
        'libwinpthread-1.dll': _compiler_install_path.joinpath('libwinpthread-1.dll')
    }
}
compiler_dll[BuildFolderType.Release] = compiler_dll[BuildFolderType.Debug]
verbose_print('\ncompiler_dll')
for key in compiler_dll:
    verbose_print(key)
    fileGroup = compiler_dll[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])

# target_compiler_dll
target_compiler_dll = {
    BuildFolderType.Debug: {
        'libgcc_s_dw2-1.dll': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('libgcc_s_dw2-1.dll'),
        'libstdc++-6.dll': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('libstdc++-6.dll'),
        'libwinpthread-1.dll': build_folder[BuildFolderType.Debug].joinpath('debug').joinpath('libwinpthread-1.dll')
    },
    BuildFolderType.Release: {
        'libgcc_s_dw2-1.dll': build_folder[BuildFolderType.Pack].joinpath('libgcc_s_dw2-1.dll'),
        'libstdc++-6.dll': build_folder[BuildFolderType.Pack].joinpath('libstdc++-6.dll'),
        'libwinpthread-1.dll': build_folder[BuildFolderType.Pack].joinpath('libwinpthread-1.dll')
    }
}
verbose_print('\ntarget_compiler_dll')
for key in target_compiler_dll:
    verbose_print(key)
    fileGroup = target_compiler_dll[key]
    for fileGroupKey in fileGroup:
        verbose_print(fileGroup[fileGroupKey])
