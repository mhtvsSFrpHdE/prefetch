// #include <QMutexLocker>
#include <QFile>
#include <QRegExp>

#include "read_thread.h"
#include "..\..\Output\stdout.h"

bool ReadThread::autoDeletePreset = true;
bool skip = false;
QMutex ReadThread::printLock(QMutex::NonRecursive);
QStringList ReadThread::excludeFolders = QStringList();

ReadThread::ReadThread(QString filePath)
{
    ReadThread::filePath = filePath;
    setAutoDelete(autoDeletePreset);
}

// *StdOut::consoleOutput << filePath
//                        << endl;
// StdOut::consoleOutput->flush();

void ReadThread::run()
{
    // QMutexLocker locker(&printLock);

    // Thread is known to skip
    if (skip)
    {
        return;
    }

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

            return;
        }
    }

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

        return;
    }
}
