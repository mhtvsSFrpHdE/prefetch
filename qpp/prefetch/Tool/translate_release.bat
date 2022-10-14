cd /d %~dp0

call qt_env.bat

cd %~dp0..

lrelease %projectName%.pro
