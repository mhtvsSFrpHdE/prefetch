cd /d %~dp0
call create_symbolic_link_env.bat
cd ..
cd ..

@REM Third party library
cd ThirdParty

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

pause