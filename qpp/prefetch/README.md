# prefetch

Ported to Q++ for better performance.

## Source code requirements

- Python: `3.10.2`
- Qt: `4.8.7`
- mingw-w64: `i686-4.8.2-release-posix-dwarf-rt_v3-rev3`

Version 4.8.7 is the last version of Qt that supports Windows XP initial version  
without any update patch, or Service Pack installed for example Windows XP SP3.  
The Qt compiler itself can even install and run on this Windows version.

## IDE

Qt Creator: `9.0.1` for debugging, VSCode for coding.  
Strongly recommend VSCode extension `TabNine` while diving into the Q++ hell.  
There are other suggest extensions added to workspace recommendations.  
IDE settings uploaded to `.vscode`, see `.vscode\README.md` for more information.

Duplicate `envExample.bat` as `env.bat` and change variables inside,  
assume you don't have global gcc instance, `env.bat` tells VSCode where to find gcc compiler files and clangd.

- `start_vscode.bat` to open VSCode.
- `start_qcreator.bat` to open Qt Creator.
- `start_ide.bat` to open both editor.
- `start_shell.bat` to open command prompt for executing gcc commands.

## clangd

Due to performance problems and newly popuped bug,  
VSCode cpptools will be replaced by clangd.  
Enable clangd in Qt Creator `Edit\Preferences\C++\clangd`,  
Then Qt Creator will generate required files.

In VSCode:

- [x] `clangd.exe`: Use the one bundled with Qt Creator, update your `env.bat`  
      Two different version clangd will override cache between each other endlessly
- [x] `compile_commands.json`: Already set in `prefetch_qpp.code-workspace`
- [x] `.clangd` Copy from Qt Creator 9 `config.yaml`, Adjusted for Qt 4.8.7
- [x] `.clang-format` Emulate VSCode cpptools formatter

## qmake build profile

Debug: `"DEFINES += LOG_ENABLED=true" "DEFINES += TEST_TRAY_MENU_ENABLED=true" "DEFINES += CONSOLE_ENABLED=true" "CONFIG += console"`  
Debug build steps: `python, build.py Debug, %{buildDir}\..\prefetch\Tool`

Release: Use default settings  
Release_Performance: `"DEFINES += TRANSLATE_ENABLED=false"`  
Release_Verbose: `"DEFINES += LOG_ENABLED=true"`
