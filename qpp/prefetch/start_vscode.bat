cd /d %~dp0

call env.bat

@set path=%path%;%qtPath%;%mingwPath%

start "" "%vsCodePath%" "%vsCodeWorkspace%"