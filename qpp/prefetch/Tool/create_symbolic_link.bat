cd /d %~dp0
call create_symbolic_link_env.bat
cd ..
cd ..

@REM Third party library
cd ThirdParty

rd "qt"
mklink /d "qt" "%qt%"

rd "boost"
mklink /d "boost" "%boost%"

cd ..

@REM cpptools cache
cd prefetch
mkdir cpptools
cd cpptools

rd "browse.databaseFile"
mklink /d "browse.databaseFile" "%browse.databaseFile%"

rd "intelliSenseCachePath"
mklink /d "intelliSenseCachePath" "%intelliSenseCachePath%"

cd ..
cd ..

@REM clangd
cd prefetch

rm "compile_commands.json"
mklink "compile_commands.json" "..\build-prefetch-Desktop_x86_windows_mingw4_8_2_32bit-Debug\.qtc_clangd\compile_commands.json"

cd ..

pause
