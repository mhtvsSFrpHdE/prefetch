#include <QMutexLocker>

#include "read_thread.h"
#include "..\..\Output\stdout.h"

QMutex ReadThread::printLock(QMutex::NonRecursive);

ReadThread::ReadThread(QString filePath)
{
    ReadThread::filePath = filePath;
}

void ReadThread::run()
{
    QMutexLocker locker(&printLock);

    *StdOut::consoleOutput << filePath
                           << endl;
    StdOut::consoleOutput->flush();
}
