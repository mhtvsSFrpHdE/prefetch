// #include <QMutexLocker>
#include <QFile>

#include "read_thread.h"
#include "..\..\Output\stdout.h"

bool ReadThread::autoDeletePreset = true;
QMutex ReadThread::printLock(QMutex::NonRecursive);

ReadThread::ReadThread(QString filePath)
{
    ReadThread::filePath = filePath;
    setAutoDelete(autoDeletePreset);
}

void ReadThread::run()
{
    // QMutexLocker locker(&printLock);

    // *StdOut::consoleOutput << filePath
    //                        << endl;
    // StdOut::consoleOutput->flush();

    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly))
    {
        auto fileBytes = file.readAll();
        file.close();
    }
}
