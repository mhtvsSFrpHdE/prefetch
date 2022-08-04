import os  # nopep8
import sys  # nopep8
from pathlib import Path  # nopep8

# Log
import logging
logging.basicConfig(filename='copy_resource.log', encoding='utf-8', level=logging.INFO)

# Append source code folder
srcPath = Path(os.path.dirname(__file__)).joinpath("src")  # nopep8
sys.path.append(srcPath)  # nopep8

# pToolCore
from Src import pToolCore  # nopep8

# Environment
cwd = Path(os.getcwd()).parent
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

# Debug DLL
if buildType == pToolCore.BuildType.Debug:
    qtPath = Path("C:\Qt\\4.8.7\\bin")

    pToolCore.Function.processFile(qtPath.joinpath("QtCored4.dll"))

    # process(qtPath.joinpath("QtDesignerComponentsd4.dll"))
    # process(qtPath.joinpath("QtDesignerd4.dll"))
    # process(qtPath.joinpath("QtHelpd4.dll"))
    # process(qtPath.joinpath("QtCLucened4.dll"))
    # process(qtPath.joinpath("QtScriptToolsd4.dll"))
    # process(qtPath.joinpath("QtWebKitd4.dll"))
    # process(qtPath.joinpath("QtDeclaratived4.dll"))
    # process(qtPath.joinpath("QtScriptd4.dll"))
    # process(qtPath.joinpath("QtSvgd4.dll"))
    # process(qtPath.joinpath("QtMultimediad4.dll"))
    # process(qtPath.joinpath("phonond4.dll"))
    # process(qtPath.joinpath("QtXmlPatternsd4.dll"))
    # process(qtPath.joinpath("QtOpenGLd4.dll"))
    # process(qtPath.joinpath("Qt3Supportd4.dll"))
    # process(qtPath.joinpath("QtGuid4.dll"))
    # process(qtPath.joinpath("QtDBusd4.dll"))
    # process(qtPath.joinpath("QtTestd4.dll"))
    # process(qtPath.joinpath("QtSqld4.dll"))
    # process(qtPath.joinpath("QtNetworkd4.dll"))
    # process(qtPath.joinpath("QtXmld4.dll"))

    # pass: Let editor fold code until here
    pass
