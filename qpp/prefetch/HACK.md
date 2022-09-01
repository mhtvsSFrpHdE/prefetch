# prefetch hack

Explain unusual code snippets.

## UI call must run on main thread

Qt may print text to console like this:

```
QObject::connect: Cannot queue arguments of type 'QTextBlock'
(Make sure 'QTextBlock' is registered using qRegisterMetaType().)
QObject::connect: Cannot queue arguments of type 'QTextCursor'
(Make sure 'QTextCursor' is registered using qRegisterMetaType().)
```

Call UI element on main thread or will get these on console.  
In order to back to main thread, emit a signal/slot pair.

https://stackoverflow.com/questions/2104779/qobject-qplaintextedit-multithreading-issues

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

## QPlainTextEdit scroll bar background update not work

```
// showEvent(QShowEvent *showEventAddress)
...
// Fix scroll bar position on restore
ui->stdOut_plainTextEdit->insertPlainText("");
scrollBarToBottom_slot();
```

During `window.hide()`, fix scroll bar position is not work, which is the same code work during `window.show()`.  
None of the following try will work:

- `ui->stdOut_plainTextEdit->verticalScrollBar()->setValue(0);`  
   `scrollBarToBottom_slot();`
- `QTimer::singleShot(0, Global::qMainWindow, SLOT(scrollBarToBottom_slot()));`
- `ui->stdOut_plainTextEdit->update();`
- `ui->stdOut_plainTextEdit->verticalScrollBar()->update();`

In the end, insert empty string seems can update the scroll bar.  
But `textChanged` signal is not fired, which is a protected signal can not emit manually.
