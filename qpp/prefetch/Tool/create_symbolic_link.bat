cd /d %~dp0
call create_symbolic_link_env.bat
cd ..
cd ..

@REM Third party library
cd ThirdParty

rd "qt"
mklink /d "qt" "%qt%"

rd "boost"
mklink /d "boost" "%boost%"

cd ..

@REM clangd
cd prefetch

rm "compile_commands.json"
mklink "compile_commands.json" "%clang_compile_commands%"

cd ..

pause
