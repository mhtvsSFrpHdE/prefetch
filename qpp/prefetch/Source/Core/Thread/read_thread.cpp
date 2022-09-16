#include <QFile>
#include <QRegExp>

#include "read_thread.h"
#include "..\..\Output\stdout.h"
#include "const_thread.h"
#include "..\..\Output\log.h"

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

bool ReadThread::run_SearchExclude()
{
    using namespace Const_ReadThread;

    // Extract folder from exclude folders
    for (int i = 0; i < excludeFolders.size(); ++i)
    {
        auto excludeFolder = excludeFolders[i];
        auto searchPattern = QRegExp(SearchPatternTemplate.arg(excludeFolder), Qt::CaseInsensitive, QRegExp::Wildcard);
        auto searchResult = filePath.indexOf(searchPattern);

        // Assume file not under exclude folder
        // Search should always not found
        // Otherwize this file is excluded
        if (searchResult != -1)
        {
            // Cache search result
            run_RequestDelete();

            return true;
        }
    }

    return false;
}

bool ReadThread::run_SearchInclude()
{
    // Extract search pattern from priority include patterns
    for (int i = 0; i < priorityIncludePatterns.size(); ++i)
    {
        auto searchPattern = QRegExp(priorityIncludePatterns[i], Qt::CaseInsensitive);
        auto searchResult = filePath.indexOf(searchPattern);

        // Assume file not match search patterns
        // Search should always not found
        // Otherwize this file is included
        if (searchResult != -1)
        {
            return true;
        }
    }

    return false;
}

void ReadThread::run_RequestDelete()
{
    QRunnable *currentThreadPointer = this;

    pendingDeleteThreadMutex.lock();
    pendingDeleteThread.append(currentThreadPointer);
    pendingDeleteThreadMutex.unlock();
}

void ReadThread::run_read()
{
    // Read file
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        auto fileBytes = file.readAll();
        file.close();
    }
    // File not available
    else
    {
        // Cache result
        run_RequestDelete();
    }
}

void ReadThread::run()
{
    // Thread is known to skip
    if (pause)
    {
        return;
    }

    if (skipSearch == false)
    {
        bool priorityInclude = run_SearchInclude();

        // Only search excluded if file not priority included
        if (priorityInclude == false)
        {
            if (run_SearchExclude())
            {
                return;
            }
        }

        skipSearch = true;
    }

    run_read();
}
