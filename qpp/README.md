# prefetch.ini

The program has no error detection,  
putting wrong value in prefetch.ini will crash the program.

## PrefetchFolder

Treat this config group as Array:

- Config under this group is key/value pair
- Key name is not matter, you can add your own
- One key have one value, for multiple folder, add new key for it
- Path splitter must be escaped, like `C:\\`

## ExcludeFolder

Same as `PrefetchFolder`.

## AfterPrefetch

These are startup items and will only run once after first prefetch  
in order to ensure they're startup in cached environment.

Same as `PrefetchFolder` and something to notice:

```
Example1=\"C:\\Program Files\\Mozilla Firefox\\firefox.exe\" https://www.mozilla.org
Example2=explorer Firefox.lnk
```

Example1 shows how do you put space in exe path and pass arguments,  
a lot things required to escape `\"` properly.

Example2 shows a smart way to isolate details from `prefetch`:

- Create or copy a lnk shortcut along with `prefetch.exe`
- Remove space from lnk name
- Write `explorer ` before lnk name in `prefetch.ini`

## Thread

### MaxThreadCount

Set to 0 to use all available CPU cores.

Qt will try to set this value automatically.  
Hyper-Threading will often double the value of real CPU cores.  
However, hard drive may not able to handle too much read thread:  
in this case, 2, 4 or 8 threads can faster than 16 threads.

There is no known best value of this setting.

### RescanInterval

Set when to rescan files from folder.  
Example:

- 0 to disable rescan
- 1 to rescan everytime

After folder scanned, all file path founded will cache to RAM,  
so future prefetch no need to scan what files to prefetch again,  
but prefetch them directly.

When a prefetch task is done, increase completed task counter.  
If completed task greater than or equal to RescanInterval,  
file path cache will be erased and rescan from folder.

For files not often change (_.dll, _.exe, etc), set to 0.  
For user data, set to 1.

For different folder types,  
deploy multiple prefetch instance is required in current version.

### PrefetchInterval

Seconds, set to 60 for prefetch every minute.
