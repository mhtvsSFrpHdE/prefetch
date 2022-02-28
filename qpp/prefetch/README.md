# prefetch

Ported to Q++ for better performance.

## Source code requirements

- Python: `3.10.2`
- Qt: `4.8.7`
- mingw-w64: `i686-4.8.2-release-posix-dwarf-rt_v3-rev3`

4.8.7 is the last version of Qt that supports Windows XP initial version  
without any update patch, or Service Pack installed for example Windows XP SP3.  
The Qt compiler itself can even install and run on this Windows version.

## IDE

Qt Creator: `6.0.2` for debugging, VSCode for coding.  
Strongly recommend VSCode extension `TabNine` while diving into the Q++ hell.  
There are other suggest extensions added to workspace recommendations.  
IDE settings uploaded to `.vscode`, see `.vscode\README.md` for more information.

Duplicate `envExample.bat` as `env.bat` and change variables inside,  
then run `start_vscode.bat` to open VSCode.  
`env.bat` tells VSCode where to find gcc compiler files.
