cd /d %~dp0

call env.bat

cd %~dp0..

lupdate -pro %projectName%.pro -ts Source\Translate\File\%langFile_en_US%

pause