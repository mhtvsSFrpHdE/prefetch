cd /d %~dp0

call env.bat

cd %~dp0..

lupdate -pro %projectName%.pro -ts %langFile_en_US%

pause