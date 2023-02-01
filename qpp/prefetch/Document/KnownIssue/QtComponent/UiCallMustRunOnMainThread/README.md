## UI call must run on main thread

Qt may print text to console like this:

```
QObject::connect: Cannot queue arguments of type 'QTextBlock'
(Make sure 'QTextBlock' is registered using qRegisterMetaType().)
QObject::connect: Cannot queue arguments of type 'QTextCursor'
(Make sure 'QTextCursor' is registered using qRegisterMetaType().)
```

Call UI element on main thread is required, or will get these on console,  
may even crash the program sometimes.  
In order to back to main thread, emit a signal/slot pair.

https://stackoverflow.com/questions/2104779/qobject-qplaintextedit-multithreading-issues
