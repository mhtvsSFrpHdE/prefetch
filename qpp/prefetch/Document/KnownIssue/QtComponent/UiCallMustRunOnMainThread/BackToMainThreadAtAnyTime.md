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
