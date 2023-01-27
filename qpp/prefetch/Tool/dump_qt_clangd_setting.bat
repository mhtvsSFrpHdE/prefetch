@REM Open project.pro with Qt Creator, wait clangd to load
wmic process where "name like 'clangd.exe'" get commandline>clangd_setting.txt