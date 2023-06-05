#include <QFile>

#include "read_file_thread.h"
#include "const_read_file_thread.h"

#define crft Const_ReadFileThread

bool ReadLoop_ReadFileThread::run_SearchExclude()
{
    // Extract folder from exclude folders
    for (int i = 0; i < excludeFolders.size(); ++i)
    {
        auto excludeFolder = excludeFolders[i];
        auto searchPattern = QRegExp(crft::SearchPatternTemplate.arg(excludeFolder), Qt::CaseInsensitive, QRegExp::Wildcard);
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

bool ReadLoop_ReadFileThread::run_SearchInclude()
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

void ReadLoop_ReadFileThread::run_RequestDelete()
{
    QRunnable *currentThreadPointer = this;

    pendingDeleteThreadMutex.lock();
    pendingDeleteThread.append(currentThreadPointer);
    pendingDeleteThreadMutex.unlock();
}

void ReadLoop_ReadFileThread::run_read_WithBuffer(QFile *file)
{
    qint64 readResult = sharedReadBufferSize;
    while (readResult > 0)
    {
        readResult = file->read(sharedReadBuffer, sharedReadBufferSize);
    }
}

void ReadLoop_ReadFileThread::run_read_Directly(QFile *file)
{
    auto fileBytes = file->readAll();
}

void ReadLoop_ReadFileThread::run_read()
{
    // Read file
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        (*run_read_action)(&file);
        file.close();
    }
    // File not available
    else
    {
        // Cache result
        run_RequestDelete();
    }
}

void ReadLoop_ReadFileThread::run()
{
    // Thread is known to skip
    if (stop)
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
