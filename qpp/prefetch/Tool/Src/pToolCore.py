import shutil
import os

from enum import Enum
from pathlib import Path


class Input:
    # Working directory
    cwd = None

    # Build type
    buildType = None


def Init(cwd, buildType):
    Input.cwd = cwd
    Input.buildType = buildType


class FolderType(Enum):
    # Example: "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release\release"
    Compile = 1
    # Example: "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release\release\pack"
    Dist = 2


class BuildType(Enum):
    Release = 1
    Debug = 2


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
    def getFolderPath(targetFileName="", folderType=FolderType.Dist):
        navigate1 = "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Debug"
        navigate2 = "debug"
        navigate3 = "pack"

        if Input.buildType == BuildType.Release:
            navigate1 = "build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Release"
            navigate2 = "release"

        outputPath = Input.cwd.parent.joinpath(navigate1)
        outputPath = outputPath.joinpath(navigate2)

        if (Input.buildType == BuildType.Debug):
            outputPath = outputPath.joinpath(targetFileName)
            return outputPath

        if (folderType == FolderType.Compile):
            return outputPath

        if (folderType == FolderType.Dist):
            outputPath = outputPath.joinpath(navigate3)
            os.makedirs(outputPath, exist_ok=True)
            outputPath = outputPath.joinpath(targetFileName)

            return outputPath

        return None

    # Check condition first, if true then run action
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

    def processFile(sourceFileName, buildType=BuildType.Release):
        sourceFilePath = Input.cwd.joinpath(sourceFileName)
        targetFilePath = Function.getFolderPath(Path(sourceFilePath.name))

        if buildType == BuildType.Release:
            Function.copy(sourceFilePath, targetFilePath)
        if buildType == BuildType.Debug:
            Function.compare(sourceFilePath, targetFilePath, Function.copy)
