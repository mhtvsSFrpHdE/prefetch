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
