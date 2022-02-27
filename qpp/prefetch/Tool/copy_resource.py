import os
import shutil
import sys

from pathlib import Path
import logging

# Environment
cwd = Path(os.getcwd()).parent

# Log
#logging.basicConfig(filename='copy_resource.log', encoding='utf-8', level=logging.INFO)

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

sourceFileName = "prefetch.ini"
sourceFilePath = cwd.joinpath(sourceFileName)
targetFilePath = getOutputPath(sourceFileName)
compare(sourceFilePath, targetFilePath, copy)