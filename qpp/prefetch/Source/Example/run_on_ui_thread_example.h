#ifndef RunOnUiThreadExample_h
#define RunOnUiThreadExample_h

#include <QObject>

#include "Hack\function_pointer_in_signal_slot.h"

// Run function pointer on UI thread
//
// run_block connect use Qt::BlockingQueuedConnection
//     So function will block until function pointer done
//     For unknown reason, only first call will work
//         2nd call will lead to dead lock (It shouldn't)
//         Careful if you do need block
//         May be same bug mentioned in Hack\QTimer and Qt event
class RunOnUiThreadExample : public QObject
{
    Q_OBJECT
public:
    void init()
    {
        MocFunctionPointer::init();
        // clang-format off
        // Qt suggest `void*` instead of `void *`
        connect(this, SIGNAL(runOnUiThread_signal(mocFunctionPointer)), this, SLOT(runOnUiThread_slot(mocFunctionPointer)), Qt::BlockingQueuedConnection);
        connect(this, SIGNAL(runOnUiThread_block_signal(mocFunctionPointer)), this, SLOT(runOnUiThread_block_slot(mocFunctionPointer)), Qt::BlockingQueuedConnection);
        connect(this, SIGNAL(runVoidPointerOnUiThread_signal(mocVoidPointerFunctionPointer,void*)), this, SLOT(runVoidPointerOnUiThread_slot(mocVoidPointerFunctionPointer,void*)), Qt::BlockingQueuedConnection);
        connect(this, SIGNAL(runVoidPointerOnUiThread_block_signal(mocVoidPointerFunctionPointer,void*)), this, SLOT(runVoidPointerOnUiThread_block_slot(mocVoidPointerFunctionPointer,void*)), Qt::BlockingQueuedConnection);
        // clang-format on
    }
    void run(mocFunctionPointer voidFunctionPointer)
    {
        emit runOnUiThread_signal(voidFunctionPointer);
    }
    // Unstable! Possible to deadlock when use twice
    void run_block(mocFunctionPointer voidFunctionPointer)
    {
        emit runOnUiThread_block_signal(voidFunctionPointer);
    }
    // Unstable! Possible to deadlock when continuous use twice
    void runVoidPointer(mocVoidPointerFunctionPointer voidPointerFunctionPointer, void *value)
    {
        emit runVoidPointerOnUiThread_signal(voidPointerFunctionPointer, value);
    }
    // Unstable! Possible to deadlock when continuous use twice
    void runVoidPointer_block(mocVoidPointerFunctionPointer voidPointerFunctionPointer, void *value)
    {
        emit runVoidPointerOnUiThread_block_signal(voidPointerFunctionPointer, value);
    }

public slots:
    void runOnUiThread_slot(mocFunctionPointer voidFunctionPointer)
    {
        (*voidFunctionPointer)();
    }
    void runOnUiThread_block_slot(mocFunctionPointer voidFunctionPointer)
    {
        (*voidFunctionPointer)();
    }
    void runVoidPointerOnUiThread_slot(mocVoidPointerFunctionPointer voidPointerFunctionPointer, void *value)
    {
        (*voidPointerFunctionPointer)(value);
    }
    void runVoidPointerOnUiThread_block_slot(mocVoidPointerFunctionPointer voidPointerFunctionPointer, void *value)
    {
        (*voidPointerFunctionPointer)(value);
    }

signals:
    void runOnUiThread_signal(mocFunctionPointer voidFunctionPointer);
    void runOnUiThread_block_signal(mocFunctionPointer voidFunctionPointer);
    void runVoidPointerOnUiThread_signal(mocVoidPointerFunctionPointer voidPointerFunctionPointer, void *value);
    void runVoidPointerOnUiThread_block_signal(mocVoidPointerFunctionPointer voidPointerFunctionPointer, void *value);
};

#endif
