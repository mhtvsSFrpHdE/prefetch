# prefetch
**What is this**  
In most cases, the Windows prefetch mechanism will not function as you wish.  
Indeed it has many smart tricks than other ancient Windows version,  
but it was still unconfigurable, result in your common software still running slow,  
even on some modern large memory hardware, e.g. greater than 16 GB.  

Let's say when you have 32 GB system memory,  
there's a lot of empty space to hold your entire software files and user data.  
But Windows won't do that(for many reasons), so when you trying to open the software,  
Windows always read them from disk instead of memory.  
That's how you won't benefit from this "prefetch" mechanism.  

The prefetch project created for this situation.  
It maintains an "include" and "exclude" folder list, written in JSON.  
Each time a preset interval triggered, it will read your software and user data into memory,  
then discard them to null.
Windows will notice the reading behavior and cache those data in memory,  
So the next time you truly run the software, you will read the software files from memory directly.  

A roughly test shows Firefox with a lot extension:
- Boot the PC, wait the disk stops reading, that shows Windows completed the prefetch.
- Open Firefox, it takes 26 seconds to load all files and ready to use.
- Reboot and wait for Windows to prefetch again, but set this "prefetch" project to run at startup.
- Open Firefox, it takes 3 seconds to load.

This is **FAST** a lot.  
The other reason to use prefetch is,  
Windows prefetch is dynamic. You can't control which files stay in the memory,  
so in daily use, you will face many cache miss to your common software,  
because Windows is **SMART ENOUGH** to discard your cache for its other purpose.  
Once you open your software, a lot cache miss still result in the long first access time.  
A preset loop executes interval can reload the cache for you periodic.  
Result in you can always use your files that smooth like cutting butter.  

**How to use**  
Use your text editor open "prefetch.ps1" but do not run it,  
check the two variables:
```
$unlimitedMode = $true
$loopInterval = 50
```
The unlimitedMode will run the prefetch every a period of time,  
set it to $false to run only once, if needed.  
And the loopInterval is the cooldown time between runs, by seconds.  

The next is use text editor open "prefetch.json",  
put your software path under "prefetchFolderArray" key,  
in some cases, there is a path in your software that you don't have to prefetch,  
for example, the big files(greater than 100~1000MB) is less valuable for cache,  
and browser cache files is really rare to use, load them also takes an extremely long time.  
So put the folder you don't want to prefetch under "excludeFolderArray".  

We mentioned the JSON format,  
the best is to learn what is JSON before you edit this "prefetch.json".  
There is some small technique character like the "," after each "]",  
sometimes after the "]", there isn't a ",".  
The path divided by "\\" instead of "\".  
To understand the difference, learn JSON if needed.
