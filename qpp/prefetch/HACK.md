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

Call UI element on main thread is required, or will get these on console,  
may even crash the program sometimes.  
In order to back to main thread, emit a signal/slot pair.

https://stackoverflow.com/questions/2104779/qobject-qplaintextedit-multithreading-issues

### Back to main thread at any time

You may also want to use function pointer to do this.  
Use MainWindow as example, in `mainwindow.h`, create signal/slot pair:

```
public slots:
    void callbackOnUiThread_slot(mocFunctionPointer callback);

signals:
    void callbackOnUiThread_signal(mocFunctionPointer callback);
```

Connect them during MainWindow init:

```
connect(this, SIGNAL(callbackOnUiThread_signal(mocFunctionPointer)), this, SLOT(callbackOnUiThread_slot(mocFunctionPointer)));
```

Create function to operate UI element, and it's wrapper:

```
// MainWindow class

// Operate UI
void MainWindow::sendCommand_restore_slot()
{
    ui->sendCommand_pushButton->setEnabled(true);
    ...
}

// Pass function pointer with signals/slots
// See `prefetch\Source\Example\Hack\function_pointer_in_signal_slot.h` for more details
void sendCommand_restore_OnUiThread_toOrdinary()
{
    Global::qMainWindow->sendCommand_restore_slot();
}

// Wrapper to operate UI
// This function will run on background thread
void MainWindow::sendCommand_restore()
{
    // emitted signal will later run it's slot on UI thread
    emit callbackOnUiThread_signal(&sendCommand_restore_slot);
}
```

Call wrapper function in background thread:

```
// Somewhere else
Global::qMainWindow->sendCommand_restore();
```

### Pass function pointer with signals/slots

The following code wont compile:

```
// mainwindow.h
...
public slots:
    void wontCompileExample_slot(void (*callback)());    // <- here
signals:
    void wontCompileExample_signal(void (*callback)());
...
```

Error message:

```
mainwindow.h:52: Parse error at "void"
Makefile.Debug:224: recipe for target 'debug/moc_mainwindow.cpp' failed
```

This declare is legal in C++, but the Qt component `moc_` will fail.  
I did found a solution can bypass the limitation by using `typedef`.

See `prefetch\Source\Example\Hack\function_pointer_in_signal_slot.h` for more details.

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
auto existText = ui->stdOut_plainTextEdit->toPlainText();
ui->stdOut_plainTextEdit->setPlainText(existText);
scrollBarToBottom_slot();
```

During `window.hide()`, fix scroll bar position is not work, which is the same code work during `window.show()`.  
None of the following try will work:

- `ui->stdOut_plainTextEdit->verticalScrollBar()->setValue(0);`  
   `scrollBarToBottom_slot();`
- `QTimer::singleShot(0, Global::qMainWindow, SLOT(scrollBarToBottom_slot()));`
- `ui->stdOut_plainTextEdit->update();`
- `ui->stdOut_plainTextEdit->verticalScrollBar()->update();`
- `ui->stdOut_plainTextEdit->insertPlainText("");`

In the end, inplace get and set seems can update the scroll bar.  
`textChanged` signal will not fire in this case, which is a protected signal can not emit manually either.
