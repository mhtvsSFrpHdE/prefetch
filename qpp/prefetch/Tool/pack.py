import os  # nopep8
import sys  # nopep8
from pathlib import Path  # nopep8

# Log
import logging
logging.basicConfig(filename='pack.log', encoding='utf-8', level=logging.INFO)

# Append source code folder
srcPath = Path(os.path.dirname(__file__)).joinpath("src")  # nopep8
sys.path.append(srcPath)  # nopep8

# pToolCore
from Src import pToolCore  # nopep8

# Environment
cwd = Path(os.getcwd()).parent
buildType = pToolCore.BuildType.Release
pToolCore.Init(cwd, buildType)

# File list

compileOutputPath = pToolCore.Function.getFolderPath(folderType=pToolCore.FolderType.Compile)

# Config
pToolCore.Function.processFile(Path("prefetch.ini"))

# Exe
pToolCore.Function.processFile(compileOutputPath.joinpath("prefetch.exe"))

# DLL
pToolCore.Function.processFile(Path("requirements").joinpath("libgcc_s_dw2-1.dll"))
pToolCore.Function.processFile(Path("requirements").joinpath("libstdc++-6.dll"))
pToolCore.Function.processFile(Path("requirements").joinpath("libwinpthread-1.dll"))
pToolCore.Function.processFile(Path("requirements").joinpath("QtCore4.dll"))
