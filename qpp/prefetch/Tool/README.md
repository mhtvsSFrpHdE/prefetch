# Tool

## envExample

Before use any tool, duplicate `*envExample.*` as `*env.*`,  
and change environment variables in `*env.*`, otherwise these tool not gonna to work.

Full list of envExample:

- `qt_envExample.bat` -> `qt_env.bat`
- `create_symbolic_link_envExample.bat` -> `create_symbolic_link_env.bat`
- `build_envExample.py` -> `build_env.py`

## bat tool

### translate_update

Generate or update Qt translate file.

### translate_delete_obsolete

Same as `translate_update`, but translate not in use will be deleted.

### translate_release

Compile Qt translate `*.ts` to `*.qm`, it's part of "Build All" task.  
So make sure qt_env is set.

### create_symbolic_link

Project use relative path to accecc library and IDE user data.  
If you want to move these folder to another drive, use symbolic link.

## python tool

Based on python 3.10.2

### build

`qmake` or Qt Creator have no simple option to **copy files if newer** after compile.  
Add a custom build step in Qt Creator that run this script, files will be copy to debug or release folder.

Example (VSCode tasks.json):

```
Command: `python`
Arguments(debug): `%{sourceDir}\Tool\build.py Debug`
Arguments(release): `%{sourceDir}\Tool\build.py Release`
Arguments(...): ...
Working directory: `%{sourceDir}\Tool`
```

## PowerShell tool

## ReCompact

The one is a atavistic evolution version of `CompactGUI`.
