# .vscode

VSCode C++ config file example.

Here are some good external reference:  
https://www.kdab.com/using-visual-studio-code-for-qt-apps-pt-1/  
https://www.kdab.com/using-visual-studio-code-for-qt-apps-pt-2/

## c_cpp_properties.json

### includePath

This settings tell VSCode where to find:

- Qt header files
- Qt Forms generated header files

### compilerPath

Contains necessary information help finding which compiler is used during develop.

### c/cppStandard

Most recent standard supported by compiler.

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

The negative effect is VSCode can't decode QString and other Qt object to puretext.  
Such defect make VSCode unuseable for debugging in most case.  
Switch back to Qt Creator if these information is necessary for debugging.

### Qt - Debug exist

Run debug use exist compiled binary.  
Although build system will consume as less as possible time if code have no change,  
it will still waste several seconds to ensure that.  
If one just reran a compiled binary while debugging,  
there is no need to enter build system.

#### miDebuggerPath

Full path of `gdb` bundled with the compiler.

#### symbolSearchPath

Tells VSCode where to find Qt symbols so you can step into Qt source.

### Qt - Build and debug

Same as `Qt - Debug exist` but will run build system before start compiled binary.  
Useful when source code are modified.

#### Python: Current File(Tool)

Run and debug py files under Tool folder.
