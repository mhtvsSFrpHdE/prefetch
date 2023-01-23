#ifndef InputLoopThread_h
#define InputLoopThread_h

#include <QThread>

#include "..\..\Example\self_delete_thread_example.h"

class InputLoopThread : public QThread
{
    Q_OBJECT
public:
    void run() override;

    // Input from remote
    void receiveText(QString input, void (*callback)() = NULL);
};

#endif
