cd /d %~dp0

call env.bat

@set path=%path%;%qtPath%;%mingwPath%;%clangdPath%

call clean_vscode.bat
@REM VSCode chromium gpu
start "" "%vsCodePath%" "%vsCodeWorkspace%" --enable-gpu-rasterization --ignore-gpu-blacklist