# Tested on Python 3.9.10
#
# No support for copy if newer to Release compile output folder
# Use run Debug without debug instead

import sys  # nopep8

# Log
import logging
logging.basicConfig(filename='build.log', encoding='utf-8', level=logging.INFO, filemode='w')

# Build setting
import build_setting  # nopep8

# Build core
import build_core as build_core  # nopep8
build_core.init(logging, verboseFromRemote=False)
verbose_print = build_core.verbose_print  # nopep8
copy_if_newer = build_core.copy_if_newer  # nopep8

# Environment
buildType = build_setting.BuildFolderType.Release
try:
    buildType = build_setting.BuildFolderTypeMap[sys.argv[1]]
except:
    breakpoint()
    pass

# Release: Collect release build together
if buildType == build_setting.BuildFolderType.Release:
    verbose_print('\nStart build Release')

    # exe
    exe = build_setting.exe
    target_exe = build_setting.target_exe
    verbose_print('\nexe')
    for key in exe:
        verbose_print(str(key) + ': ' + str(exe[key]))
        copy_if_newer(exe[key], target_exe[key])

    # config
    config = build_setting.config[buildType]
    target_config = build_setting.target_config[buildType]
    verbose_print('\nconfig')
    for key in config:
        verbose_print(key + ': ' + str(config[key]))
        copy_if_newer(config[key], target_config[key])

    # qt_translate
    qt_translate = build_setting.qt_translate[buildType]
    target_qt_translate = build_setting.target_qt_translate[buildType]
    verbose_print('\nqt_translate')
    for key in qt_translate:
        verbose_print(str(key) + ': ' + str(qt_translate[key]))
        copy_if_newer(qt_translate[key], target_qt_translate[key])

    # prefetch_translate
    prefetch_translate = build_setting.prefetch_translate[buildType]
    target_prefetch_translate = build_setting.target_prefetch_translate[buildType]
    verbose_print('\nprefetch_translate')
    for key in prefetch_translate:
        verbose_print(str(key) + ': ' + str(prefetch_translate[key]))
        copy_if_newer(prefetch_translate[key], target_prefetch_translate[key])

    # qt_dll
    qt_dll = build_setting.qt_dll[buildType]
    target_qt_dll = build_setting.target_qt_dll[buildType]
    verbose_print('\nqt_dll')
    for key in qt_dll:
        verbose_print(key + ': ' + str(qt_dll[key]))
        copy_if_newer(qt_dll[key], target_qt_dll[key])

    # compiler_dll
    compiler_dll = build_setting.compiler_dll[buildType]
    target_compiler_dll = build_setting.target_compiler_dll[buildType]
    verbose_print('\ncompiler_dll')
    for key in compiler_dll:
        verbose_print(key + ': ' + str(compiler_dll[key]))
        copy_if_newer(compiler_dll[key], target_compiler_dll[key])

# Debug: Only to debug build folder
if buildType == build_setting.BuildFolderType.Debug:
    verbose_print('\nStart build Debug')

    # config
    config = build_setting.config[buildType]
    target_config = build_setting.target_config[buildType]
    verbose_print('\nconfig')
    for key in config:
        verbose_print(key + ': ' + str(config[key]))
        copy_if_newer(config[key], target_config[key])

    # qt_translate
    qt_translate = build_setting.qt_translate[buildType]
    target_qt_translate = build_setting.target_qt_translate[buildType]
    verbose_print('\nqt_translate')
    for key in qt_translate:
        verbose_print(str(key) + ': ' + str(qt_translate[key]))
        copy_if_newer(qt_translate[key], target_qt_translate[key])

    # prefetch_translate
    prefetch_translate = build_setting.prefetch_translate[buildType]
    target_prefetch_translate = build_setting.target_prefetch_translate[buildType]
    verbose_print('\nprefetch_translate')
    for key in prefetch_translate:
        verbose_print(str(key) + ': ' + str(prefetch_translate[key]))
        copy_if_newer(prefetch_translate[key], target_prefetch_translate[key])

    # qt_dll
    qt_dll = build_setting.qt_dll[buildType]
    target_qt_dll = build_setting.target_qt_dll[buildType]
    verbose_print('\nqt_dll')
    for key in qt_dll:
        verbose_print(key + ': ' + str(qt_dll[key]))
        copy_if_newer(qt_dll[key], target_qt_dll[key])

    # compiler_dll
    compiler_dll = build_setting.compiler_dll[buildType]
    target_compiler_dll = build_setting.target_compiler_dll[buildType]
    verbose_print('\ncompiler_dll')
    for key in compiler_dll:
        verbose_print(key + ': ' + str(compiler_dll[key]))
        copy_if_newer(compiler_dll[key], target_compiler_dll[key])

# Preapre: Create all build folder if not exist
if buildType == build_setting.BuildFolderType.Prepare:
    verbose_print('\nStart build Prepare')

    # build_folder
    build_folder = build_setting.build_folder
    verbose_print('\nbuild_folder')
    for key in build_folder:
        verbose_print(str(key) + ': ' + str(build_folder[key]))
        build_folder[key].mkdir(parents=True, exist_ok=True)
