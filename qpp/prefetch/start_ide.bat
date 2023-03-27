cd /d %~dp0

call env.bat

start "" "%qtCreatorPath%" %qtProject%

@REM VSCode chromium gpu
start "" "%vsCodePath%" "%vsCodeWorkspace%" --enable-gpu-rasterization --ignore-gpu-blacklist