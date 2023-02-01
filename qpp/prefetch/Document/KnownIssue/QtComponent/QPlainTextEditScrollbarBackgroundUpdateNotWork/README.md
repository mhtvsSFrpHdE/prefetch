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
