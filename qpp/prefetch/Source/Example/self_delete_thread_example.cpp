#include "self_delete_thread_example.h"

SlefDeleteThreadExample::SlefDeleteThreadExample(QThread *thread)
{
    SlefDeleteThreadExample::thread = thread;
    connect(thread, SIGNAL(finished()), this, SLOT(deleteThis()));
}

void SlefDeleteThreadExample::deleteThis()
{
    delete thread;
    deleteLater();
    // delete this;
}
