#include <QRegExp>

#include "read_thread.h"
#include "..\..\..\Output\stdout.h"
#include "..\..\..\Output\log.h"

bool ReadThread::autoDeletePreset = true;
QStringList ReadThread::excludeFolders = QStringList();
QStringList ReadThread::priorityIncludePatterns = QStringList();
bool ReadThread::pause = false;
QMutex *ReadThread::pauseMutex = NULL;
QList<QRunnable *> ReadThread::pendingDeleteThread = QList<QRunnable *>();
QMutex ReadThread::pendingDeleteThreadMutex(QMutex::NonRecursive);
char *ReadThread::sharedReadBuffer;
int ReadThread::sharedReadBufferSize;
void (*ReadThread::run_read_action)(QFile *);
void (*ReadThread::newSharedReadBuffer_action)();
void (*ReadThread::deleteSharedReadBuffer_action)();

void ReadThread::newSharedReadBuffer_WithBuffer()
{
    sharedReadBuffer = new char[sharedReadBufferSize];
}

void ReadThread::newSharedReadBuffer_Directly()
{
    // Do nothing
}

void ReadThread::deleteSharedReadBuffer_WithBuffer()
{
    delete sharedReadBuffer;
}

void ReadThread::deleteSharedReadBuffer_Directly()
{
    // Do nothing
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
