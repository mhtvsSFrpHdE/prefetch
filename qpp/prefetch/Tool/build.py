# Tested on Python 3.9.10

import os  # nopep8
import sys  # nopep8
from pathlib import Path  # nopep8

# Log
import logging
logging.basicConfig(filename='build.log', encoding='utf-8', level=logging.INFO)

# Append source code folder
srcPath = Path(os.path.dirname(__file__)).joinpath("src")  # nopep8
sys.path.append(srcPath)  # nopep8

# pToolCore
from Src import pToolCore  # nopep8

# Environment
cwd = Path(os.getcwd()).parent
buildType = pToolCore.BuildType.Release
if (len(sys.argv) > 1):
    if sys.argv[1] == "Debug":
        buildType = pToolCore.BuildType.Debug
pToolCore.Init(cwd, buildType)

# File list

# Config
pToolCore.Function.processFile(Path("prefetch.ini"))

# DLL
pToolCore.Function.processFile(Path("requirements").joinpath("libgcc_s_dw2-1.dll"))
pToolCore.Function.processFile(Path("requirements").joinpath("libstdc++-6.dll"))
pToolCore.Function.processFile(Path("requirements").joinpath("libwinpthread-1.dll"))
pToolCore.Function.processFile(Path("requirements").joinpath("QtCore4.dll"))

if buildType == pToolCore.BuildType.Release:
    compileOutputPath = pToolCore.Function.getFolderPath(folderType=pToolCore.FolderType.Compile)

    # Exe
    pToolCore.Function.processFile(compileOutputPath.joinpath("prefetch.exe"))

if buildType == pToolCore.BuildType.Debug:
    qtPath = Path("C:\Qt\\4.8.7\\bin")

    pToolCore.Function.processFile(qtPath.joinpath("QtCored4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtDesignerComponentsd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtDesignerd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtHelpd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtCLucened4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtScriptToolsd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtWebKitd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtDeclaratived4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtScriptd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtSvgd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtMultimediad4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("phonond4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtXmlPatternsd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtOpenGLd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("Qt3Supportd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtGuid4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtDBusd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtTestd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtSqld4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtNetworkd4.dll"))
    # pToolCore.Function.processFile(qtPath.joinpath("QtXmld4.dll"))
