# prefetch

Ported to Q++ for better performance.

## Source code requirements

- Python: `3.10.2`
- Qt: `4.8.7`
- mingw-w64: `i686-4.8.2-release-posix-dwarf-rt_v3-rev3`

Version 4.8.7 is the last version of Qt that supports Windows XP initial version  
without any update patch, or Service Pack installed for example Windows XP SP3.  
The Qt compiler itself can even install and run on this Windows version.

## IDE

Qt Creator: `6.0.2` for debugging, VSCode for coding.  
Strongly recommend VSCode extension `TabNine` while diving into the Q++ hell.  
There are other suggest extensions added to workspace recommendations.  
IDE settings uploaded to `.vscode`, see `.vscode\README.md` for more information.

Duplicate `envExample.bat` as `env.bat` and change variables inside,  
assume you don't have global gcc instance, `env.bat` tells VSCode where to find gcc compiler files.

- `start_vscode.bat` to open VSCode.
- `start_qcreator.bat` to open Qt Creator.
- `start_ide.bat` to open both editor.
- `start_shell.bat` to open command prompt for executing gcc commands.

## WARNING: VSCode cpptools

Check [HDD ultimate performance guide](https://github.com/mhtvsSFrpHdE/prefetch/wiki/Frequently-asked-questions#hdd-ultimate-performance-guide) first before any modification.  
Ramdisk or GpuRamdisk perform very well with compression too.  
This extension have terrible design. It have two obviously performance bottoneck:

### Bugged `.BROWSE.VC.DB`

The one contains include information, VSCode will parse include path to this database,  
then use them to analysis C++ source file.

However, when using giant library like `Qt` and `boost`, VSCode can take a century to iterate through file system,  
and save 70000+ file information to `.BROWSE.VC.DB`.  
Until it was finished, CPU and hard disk never gets a rest.

This is not the worst, everytime a VSCode close/open, cpptools may drop entire database and create from zero.  
I collect some information about when the database can lost:

- Close VSCode during "Parsing workspase files"  
   This can happen if you added new library to include path recently.
- You did a database backup and restore  
   But when backup, `.BROWSE.VC.DB-shm` and `.BROWSE.VC.DB-wal` exist on disk.  
   Even if VSCode is safe shutdown(not parsing), sometimes the two file can still exist.  
   Do not restore these two small files, and delete the two exist before start VSCode,  
   or cpptools can refuse to accept the restore.
- Start VSCode, however there is `.BROWSE.VC.DB-shm` and `.BROWSE.VC.DB-wal` exist:  
   Although you have did nothing wrong, but you're running out of luck.

Therefore, open VSCode and wait the parse to complete,  
close VSCode and backup the `.BROWSE.VC.DB` is necessary.  
You will find it very useful one day.

Enable NTFS compress on db folder reduce size from `1.05GB` to `513MB`.

### IPCH cache

Let's just accept these files are important for new IntelliSense to work fast.  
They are also means everytime do Ctrl+S save edited source code,  
390 MB will write to disk. There is no "reuse exist file".

The file is default save to operating system drive maybe %appdata%,  
So I move them to ramdisk partition.

If these file are moved to hard disk by using `C_Cpp.intelliSenseCachePath`,  
You can witness very funny things that is a cache is much slower than disable cache.  
Compress these file using `7z lzma2 fastest`, can reduce total size from `2.19GB` to `190MB`.  
I'm pretty sure my SSD nand lifespan were abused.

Enable NTFS compress on ipch folder reduce size from `2.19GB` to `615MB`.

### Temporary solution

After days of investigation, some solution were discovered to optimize extension performance:  
https://github.com/microsoft/vscode-cpptools/issues/9837#issuecomment-1247146528
