## QTimer and Qt event

```
QTimer::singleShot(0, <object> <slot>);
```

When Qt GUI in certain status, the requested action will have no effect:

If I do `window.show()` first, then a nonsense QTimer is required to do `window.setWindowState()`  
It seems the current function must be returned, and keep executing target function from somewhere else  
The bug should be related to Qt internal event system and I can't do much things about it

Everytime a `QTimer 0` appears, means something is not work without this.

> As a special case, a QTimer with a timeout of 0 will time out as soon as all the events in the window system's event queue have been processed.  
> http://qt-project.org/doc/qt-4.8/qtimer.html#details  
> https://stackoverflow.com/questions/3332257/how-do-i-properly-implement-a-minimize-to-tray-function-in-qt
