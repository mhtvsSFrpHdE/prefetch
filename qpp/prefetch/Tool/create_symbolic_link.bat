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

pause
