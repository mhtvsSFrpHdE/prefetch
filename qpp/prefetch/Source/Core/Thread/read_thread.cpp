#include <QFile>
#include <QRegExp>

#include "read_thread.h"
#include "..\..\Output\stdout.h"

bool ReadThread::autoDeletePreset = true;
QMutex ReadThread::printLock(QMutex::NonRecursive);
QStringList ReadThread::excludeFolders = QStringList();
QStringList ReadThread::priorityIncludePatterns = QStringList();
bool ReadThread::pause = false;

ReadThread::ReadThread(QString filePath)
{
    ReadThread::filePath = filePath;
    ReadThread::skip = false;

    setAutoDelete(autoDeletePreset);
}

bool ReadThread::run_SearchExclude()
{
    // %1: Qt format path, something like "C:/"
    auto searchPatternTemplate = QString("%1*");

    // Extract folder from exclude folders
    for (int i = 0; i < excludeFolders.size(); ++i)
    {
        auto excludeFolder = excludeFolders[i];
        auto searchPattern = QRegExp(searchPatternTemplate.arg(excludeFolder), Qt::CaseInsensitive, QRegExp::Wildcard);
        auto searchResult = filePath.indexOf(searchPattern);

        // Assume file not under exclude folder
        // Search should always not found
        // Otherwize this file is excluded
        if (searchResult != -1)
        {
            // Cache search result
            skip = true;

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
        skip = true;
    }
}

void ReadThread::run()
{
    // Thread is known to skip
    if (skip || pause)
    {
        return;
    }

    bool priorityInclude = run_SearchInclude();

    // Only search excluded if file not priority included
    if (priorityInclude == false)
    {
        if (run_SearchExclude())
        {
            return;
        }
    }

    run_read();
}
