# Tool

## bat tool

### envExample

Before use any bat tool, duplicate `envExample.bat` as `env.bat`,  
and change variables in `env.bat`, otherwise these tool not gonna to work.

### update_translate

Generate or update Qt translate file.

## python tool

Based on python 3.10.2

### copy_resource

`qmake` or Qt Creator have no simple option to **copy files if newer** after compile.  
Add a custom build step in Qt Creator that run this script, files will be copy to debug or release folder.

Command: `python`  
Arguments(debug): `%{sourceDir}\Tool\copy_resource.py`  
Arguments(release): `%{sourceDir}\Tool\copy_resource.py Release`  
Working directory: `%{sourceDir}\Tool`
