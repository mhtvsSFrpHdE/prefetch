cd /d %~dp0

call env.bat

cd %~dp0..

lrelease %projectName%.pro

pause