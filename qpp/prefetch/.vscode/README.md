# .vscode

VSCode C++ config file example.

Here are some good external reference:  
https://www.kdab.com/using-visual-studio-code-for-qt-apps-pt-1/  
https://www.kdab.com/using-visual-studio-code-for-qt-apps-pt-2/

## tasks.json

### Qt Build(Debug)

Build source code but in VSCode, without leaving VSCode and switch to Qt Creator.  
The good news is because of that, `tasks.json` contains every necessary information to build.

There are several build steps but not need to care about:

- Qt qmake
- Qt mingw32-make
- Qt copy_resource

Just simply run `Qt Build(Debug)` and they will execute in correct order.  
For `copy_resource`, `python.exe` need add to PATH.

## launch.json

### Known issue

#### visualizerFile doesn't work when using gdb with Qt 4.8.7 for example Qt4.natvis

`-var-create: unable to create variable object`

The negative effect is VSCode can't decode QString and other Qt object to puretext.  
Such defect make VSCode unuseable for debugging in most case.  
Switch back to Qt Creator if these information is necessary for debugging.

#### Python: Current File(Tool)

Run and debug py files under Tool folder.
