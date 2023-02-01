## Alt QMutex to QSemaphore in most case

According to the documentation of QMutex this results in an error:

> Attempting to unlock a mutex in a different thread to the one that locked it results in an error.

But instead of a QMutex you can use a QSemaphore as a binary semaphore, to achieve the wanted behavior.

```
//create
QSemaphore semaphore(1);

//lock in thread 1
semaphore.acquire();

//unlock in thread 2
semaphore.release();
```

If a mutex is meant to be unlocked from another thread, go with QSemaphore.

https://stackoverflow.com/a/28670244
https://doc.qt.io/archives/qt-4.8/qmutex.html
