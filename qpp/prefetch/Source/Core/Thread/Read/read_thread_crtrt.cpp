#include <QRegExp>

#include "read_thread_crtrt.h"
#include "..\..\..\Output\stdout.h"
#include "..\..\..\Output\log.h"

bool ReadThread::autoDeletePreset = true;
QStringList ReadThread::excludeFolders = QStringList();
QStringList ReadThread::priorityIncludePatterns = QStringList();
bool ReadThread::pause = false;
QList<QRunnable *> ReadThread::pendingDeleteThread = QList<QRunnable *>();
QMutex ReadThread::pendingDeleteThreadMutex(QMutex::NonRecursive);
void ReadThread::lockPendingDeleteThread()
{
    // Too much of them only turn on if serious problem occur
    // LAST_KNOWN_POSITION(3)
    pendingDeleteThreadMutex.lock();
}

void ReadThread::unlockPendingDeleteThread()
{
    pendingDeleteThreadMutex.unlock();
    // Too much of them only turn on if serious problem occur
    // LAST_KNOWN_POSITION(4)
}

ReadThread::ReadThread(QString filePath)
{
    ReadThread::filePath = filePath;

    setAutoDelete(autoDeletePreset);
}
