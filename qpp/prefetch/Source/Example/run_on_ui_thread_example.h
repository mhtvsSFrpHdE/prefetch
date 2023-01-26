#ifndef RunOnUiThreadExample_h
#define RunOnUiThreadExample_h

#include <QObject>

#include "Hack\function_pointer_in_signal_slot.h"

// Run function pointer on UI thread
class RunOnUiThreadExample : public QObject
{
    Q_OBJECT
public:
    void init()
    {
        MocFunctionPointer::init();
        connect(this, SIGNAL(runOnUiThread_signal(mocFunctionPointer)), this, SLOT(runOnUiThread_slot(mocFunctionPointer)));
    }
    void runVoid(mocFunctionPointer voidFunctionPointer)
    {
        emit runOnUiThread_signal(voidFunctionPointer);
    }
public slots:
    void runOnUiThread_slot(mocFunctionPointer voidFunctionPointer)
    {
        (*voidFunctionPointer)();
    }
signals:
    void runOnUiThread_signal(mocFunctionPointer voidFunctionPointer);
};

#endif
