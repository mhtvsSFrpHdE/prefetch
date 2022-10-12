cd /d %~dp0

call env.bat

cd %~dp0..

set langFile_en_US=prefetch_en_US.ts
lupdate -pro %projectName%.pro -noobsolete -ts Source\Translate\File\%langFile_en_US%

set langFile_zh_CN=prefetch_zh_CN.ts
lupdate -pro %projectName%.pro -noobsolete -ts Source\Translate\File\%langFile_zh_CN%

pause