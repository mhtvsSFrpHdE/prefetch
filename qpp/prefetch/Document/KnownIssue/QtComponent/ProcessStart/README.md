## ProcessStart

```
    QProcess process;
    process.startDetached(fileName);
```

If run other process, exit self, when code run too fast,  
desired process may not run (QProcess::waitForStarted also not work).

Run sleep manually can fix this, even msleep(0) will do the trick, strange.

```
    QProcess process;
    process.startDetached(fileName);
    msleep(0);
```
