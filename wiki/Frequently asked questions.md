# Frequently asked questions

## Can I use source code for...

Start from 1.3 (not include 1.3), source code publish under "JDBM License" together with AGPL.  
See https://github.com/mhtvsSFrpHdE/jdbm-license/blob/main/LICENSE_JDBM  
You can either choose AGPL version or convert JDBM to compatible with what you are using.

## This is file based, how to selective cache virtual machine disk file or database?

For virtual machine, deploy prefetch instance inside each of it.  
For database, good luck with some SSHD solutions.

## Compare to other solutions

### For SSHD software like (sort by name)

- AMD StoreMI/FuzeDrive
- Intel CAS
- PrimoCache

Disadvantages:

- These software count disk usage frequency by sector,<br>
  and usually you can't specify what to hold in cache: this process rely on algorithm.<br>
  Some are good, others just act like a joke.<br>
- For Intel CAS, it won't cache Windows system files, so startup time is still slow.<br>
  There is no way to bypass the limitation.
- Price.

Advantages:

- The good is they can load data from SSD, which is much faster than HDD,<br>
  may allow system startup faster, or may not, depending on how you use them.

### For RAMDisk software like (sort by name)

- AMD Radeon RAMDisk
- virtimus/imdisk (Open source)
- prsyahmi/GpuRamDrive (Open source)

Disadvantages:

- These software take fixed amount of RAM/GRAM to create a virtual partition even if empty.
- If install software inside it (save as image mode), once have to dismount for any reason,<br>
  can't access files until mount again.
- If not install software inside it (browser cache), you still open them from slow HDD.
- Price if you choose a commercial one.

### Special - Diskeeper DRAM caching

Disadvantages:

- No SSHD support, only RAM cache.
- Max cache size limit to 12 GB for unknown reason,<br>
  their customer support provided useless solution (say to reset default settings).
- Price.

Advantages:

- Although this one use "by sector" algorithm,<br>
  it can preload files you specified by command line.<br>
  I'm planning to integrate "prefetch" with this one...

### Special - eBoostr

Disadvantages:

- Bad cache algorithm works only 10% of the time.<br>
  For example, very prefer to cache image files, why?
- Price.

Advantages:

- SSHD support.
- Allow custom cache priority (not fully customizable...)

### Finally - mhtvsSFrpHdE/prefetch

Disadvantages:

- No SSHD support, only RAM cache.
- No algorithm, rely on manually user config.
- Not a driver level solution, rely on operating system cache mechanism.<br>
  Depending on platform, effect can differ.
- Official build only support Windows platform.

Advantages:

- By use fully customized user config, indeed speed up Firefox startup.
- Work on user level so can integrate with any other SSHD solutions and Diskeeper.<br>
  Or called custom what to cache to benefit from SSHD.
- Price.
