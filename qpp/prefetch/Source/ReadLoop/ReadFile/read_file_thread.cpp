#include <QRegExp>

#include "read_file_thread.h"

bool ReadLoop_ReadFileThread::autoDeletePreset = true;
QStringList ReadLoop_ReadFileThread::excludeFolders = QStringList();
QStringList ReadLoop_ReadFileThread::priorityIncludePatterns = QStringList();
bool ReadLoop_ReadFileThread::stop = false;
QSemaphore *ReadLoop_ReadFileThread::stopSemaphore = NULL;
QList<QRunnable *> ReadLoop_ReadFileThread::pendingDeleteThread = QList<QRunnable *>();
QMutex ReadLoop_ReadFileThread::pendingDeleteThreadMutex(QMutex::NonRecursive);
char *ReadLoop_ReadFileThread::sharedReadBuffer;
int ReadLoop_ReadFileThread::sharedReadBufferSize;
void (*ReadLoop_ReadFileThread::run_read_action)(QFile *);
void (*ReadLoop_ReadFileThread::newSharedReadBuffer_action)();
void (*ReadLoop_ReadFileThread::deleteSharedReadBuffer_action)();

void ReadLoop_ReadFileThread::newSharedReadBuffer_WithBuffer()
{
    sharedReadBuffer = new char[sharedReadBufferSize];
}

void ReadLoop_ReadFileThread::newSharedReadBuffer_Directly()
{
    // Do nothing
}

void ReadLoop_ReadFileThread::deleteSharedReadBuffer_WithBuffer()
{
    delete sharedReadBuffer;
}

void ReadLoop_ReadFileThread::deleteSharedReadBuffer_Directly()
{
    // Do nothing
}

ReadLoop_ReadFileThread::ReadLoop_ReadFileThread(QString filePath, bool skipSearch)
{
    ReadLoop_ReadFileThread::filePath = filePath;
    ReadLoop_ReadFileThread::skipSearch = skipSearch;

    setAutoDelete(autoDeletePreset);
}
