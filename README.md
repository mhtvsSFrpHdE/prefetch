# prefetch

## Download

https://github.com/mhtvsSFrpHdE/prefetch/releases

## How to use

- [prefetch.ini](https://github.com/mhtvsSFrpHdE/prefetch/wiki/prefetch.ini)
- [prefetch.cache.ini](https://github.com/mhtvsSFrpHdE/prefetch/wiki/prefetch.cache.ini)
- [Command interface](https://github.com/mhtvsSFrpHdE/prefetch/wiki/Command-interface)
- [Tray icon interface](https://github.com/mhtvsSFrpHdE/prefetch/wiki/Tray-icon-interface)

## Frequently asked questions

https://github.com/mhtvsSFrpHdE/prefetch/wiki/Frequently-asked-questions

## What is this

Load program file to RAM before use, so they may perform faster.  
Designed to speed up browser like Firefox at the beginning.  
Other HDD heavy program may benefit from it like 3DS Max.

## System requirement

- 16 GB System RAM, or at least to prepare 4 GB "Available RAM" can reserve for cache.

> "Available" is the one in Windows Task Manager Memory tab.

## Background

In most cases, the Windows prefetch mechanism will not function as you wish.  
Indeed, it has many smart tricks than other ancient Windows version,  
but it was still not configurable, your common software result in running slow,  
even on some modern large memory hardware, e.g. greater than 16 GB.

Let's say when you have 32 GB system memory,  
there's a lot of empty space to hold your entire software files and user data.  
But Windows won't do that, so when you are trying to open the software,  
Windows always read them from disk instead of memory.  
That's how you won't benefit from this "prefetch" mechanism.

The prefetch project created for this situation:  
It maintains an "include" and "exclude" folder list.  
Each time a preset interval triggered, it will read your software and user data into memory,  
then discard them to null.
Windows will notice the reading behavior and cache those data in memory,  
So the next time you truly run the software, you will read the software files from memory directly.

A roughly test shows Firefox with a lot of extension:

- Boot the PC, wait the disk stops reading, that shows Windows completed the prefetch.
- Open Firefox, it takes 26 seconds to load all files and ready to use.
- Reboot and wait for Windows to prefetch again, but set this "prefetch" project to run at startup.
- Open Firefox, it takes 3 seconds to load.

This is **FAST** a lot.  
The other reason to use prefetch is,  
Windows prefetch is dynamic. You can't control which files stay in the memory,  
so in daily use, you will face many cache miss to your common software,  
because Windows is preferred to discard your cache for its other purpose.  
Once you open your software, a lot of cache miss still result in the long first access time.  
A preset loop executes interval can reload the cache for you periodic.  
Result in you can always use your files that smooth like cutting butter.
