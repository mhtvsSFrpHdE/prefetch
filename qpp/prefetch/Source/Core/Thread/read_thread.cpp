#include <QThread>

#include "read_thread.h"
#include "..\..\Output\stdout.h"

ReadThread::ReadThread(QString filePath)
{
    ReadThread::filePath = filePath;
}

void ReadThread::run()
{
    *StdOut::consoleOutput << "hello from worker thread " << QThread::currentThread()
                           << endl;
}