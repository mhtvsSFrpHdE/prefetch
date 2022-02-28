import os
import shutil
import sys

from pathlib import Path
import logging

# Environment
cwd = Path(os.getcwd()).parent

# Log
logging.basicConfig(filename='copy_resource.log', encoding='utf-8', level=logging.INFO)

# Input
buildType = "Debug"
if (len(sys.argv) > 1):
    buildType = sys.argv[1]

# Function
def compare(sourceFilePath, targetFilePath, action=None):
    # Only check if target file already exist to avoid error
    if targetFilePath.is_file():
        sourceFileTime = os.path.getmtime(sourceFilePath)
        targetFileTime = os.path.getmtime(targetFilePath)

        if sourceFileTime > targetFileTime:
            action(sourceFilePath, targetFilePath)
    # Target file not exist copy directly
    else:
        action(sourceFilePath, targetFilePath)

def copy(sourceFilePath, targetFilePath):
    shutil.copyfile(sourceFilePath, targetFilePath)

def getOutputPath(targetFileName):
    navigate1 = "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Debug"
    navigate2 = "debug"
    if buildType == "Release":
        navigate1 = "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release"
        navigate2 = "release"

    outputPath = cwd.parent.joinpath(navigate1)
    outputPath = outputPath.joinpath(navigate2)
    outputPath = outputPath.joinpath(targetFileName)

    return outputPath

def process(sourceFileName, copyWithFolder=False):
    sourceFilePath = cwd.joinpath(sourceFileName)

    if copyWithFolder:
        targetFilePath = getOutputPath(sourceFileName)
    else:
        targetFilePath = getOutputPath(Path(sourceFilePath.name))

    compare(sourceFilePath, targetFilePath, copy)

# File list

# Config
process(Path("prefetch.ini"))

# DLL
process(Path("requirements").joinpath("libgcc_s_dw2-1.dll"))
process(Path("requirements").joinpath("libstdc++-6.dll"))
process(Path("requirements").joinpath("libwinpthread-1.dll"))
process(Path("requirements").joinpath("QtCore4.dll"))

# Debug DLL
if buildType == "Debug":
    qtPath = Path("C:\Qt\\4.8.7\\bin")

    process(qtPath.joinpath("QtCored4.dll"))

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
