#include <QRegExp>

#include "read_file_thread.h"

bool Core_ReadFileThread::autoDeletePreset = true;
QStringList Core_ReadFileThread::excludeFolders = QStringList();
QStringList Core_ReadFileThread::priorityIncludePatterns = QStringList();
bool Core_ReadFileThread::stop = false;
QSemaphore *Core_ReadFileThread::stopSemaphore = NULL;
QList<QRunnable *> Core_ReadFileThread::pendingDeleteThread = QList<QRunnable *>();
QMutex Core_ReadFileThread::pendingDeleteThreadMutex(QMutex::NonRecursive);
char *Core_ReadFileThread::sharedReadBuffer;
int Core_ReadFileThread::sharedReadBufferSize;
void (*Core_ReadFileThread::run_read_action)(QFile *);
void (*Core_ReadFileThread::newSharedReadBuffer_action)();
void (*Core_ReadFileThread::deleteSharedReadBuffer_action)();

void Core_ReadFileThread::newSharedReadBuffer_WithBuffer()
{
    sharedReadBuffer = new char[sharedReadBufferSize];
}

void Core_ReadFileThread::newSharedReadBuffer_Directly()
{
    // Do nothing
}

void Core_ReadFileThread::deleteSharedReadBuffer_WithBuffer()
{
    delete sharedReadBuffer;
}

void Core_ReadFileThread::deleteSharedReadBuffer_Directly()
{
    // Do nothing
}

Core_ReadFileThread::Core_ReadFileThread(QString filePath, bool skipSearch)
{
    Core_ReadFileThread::filePath = filePath;
    Core_ReadFileThread::skipSearch = skipSearch;

    setAutoDelete(autoDeletePreset);
}
