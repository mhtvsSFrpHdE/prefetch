cd /d %~dp0

call env.bat

@set path=%path%;%qtPath%;%mingwPath%;%clangdPath%

explorer %qtProject%

@REM VSCode chromium gpu
start "" "%vsCodePath%" "%vsCodeWorkspace%" --enable-gpu-rasterization --ignore-gpu-blacklist