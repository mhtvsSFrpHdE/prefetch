cd /d %~dp0

call env.bat

@set path=%path%;%qtPath%;%mingwPath%

explorer %qtProject%
start "" "%vsCodePath%" "%vsCodeWorkspace%"