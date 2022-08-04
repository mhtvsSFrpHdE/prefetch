import shutil
import os

from enum import Enum
from pathlib import Path

# Working directory
_cwd = None


def Init(cwd):
    # Set working directory
    global _cwd
    _cwd = cwd


class FolderType(Enum):
    # Example: "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release\release"
    Compile = 1
    # Example: "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release\release\pack"
    Dist = 2


class BuildType(Enum):
    Release = 1
    # I don't see it's necessary to pack debug files
    # Debug = 2


class Function:
    # Wrap copy file to prevent change copy method in future
    #
    def copy(sourceFilePath, targetFilePath):
        shutil.copyfile(sourceFilePath, targetFilePath)

    # Get folder depending on folder type
    #     cwd: Where "main.cpp" stored, usually is "cwd = Path(os.getcwd()).parent"
    #     targetFileName: If not empty string, will add as "outputPath.joinpath(targetFileName)"
    #     folderType: See FolderType(Enum) for more details
    #     buildType: See FolderType(Enum) for more details
    def getFolderPath(targetFileName="", folderType=FolderType.Dist, buildType=BuildType.Release):
        navigate1 = ""
        navigate2 = ""
        navigate3 = "pack"

        if buildType == BuildType.Release:
            navigate1 = "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release"
            navigate2 = "release"

        outputPath = _cwd.parent.joinpath(navigate1)
        outputPath = outputPath.joinpath(navigate2)

        if (folderType == FolderType.Compile):
            return outputPath

        outputPath = outputPath.joinpath(navigate3)
        os.makedirs(outputPath, exist_ok=True)
        outputPath = outputPath.joinpath(targetFileName)

        return outputPath

    def processFile(sourceFileName):
        sourceFilePath = _cwd.joinpath(sourceFileName)
        targetFilePath = Function.getFolderPath(Path(sourceFilePath.name))

        Function.copy(sourceFilePath, targetFilePath)
