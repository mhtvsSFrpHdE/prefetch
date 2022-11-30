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
char *ReadThread::sharedReadBuffer;
int ReadThread::sharedReadBufferSize;
void (*ReadThread::run_read_action)(QFile *);
bool ReadThread::useBuffer;

void ReadThread::newSharedReadBuffer()
{
    if (useBuffer)
    {
        sharedReadBuffer = new char[sharedReadBufferSize];
    }
}
void ReadThread::deleteSharedReadBuffer()
{
    delete sharedReadBuffer;
}

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
