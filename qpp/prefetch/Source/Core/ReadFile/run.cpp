#include <QElapsedTimer>

#include "read_file.h"
#include "..\const_core.h"
#include "..\..\Output\stdout.h"
#include "..\Thread\read_thread.h"
#include "run_sleep.h"
#include "..\startup.h"
#include "..\scan_cache.h"
#include "run_timer.h"

void run_runThreadPool_DeleteExcludedFile(QList<QRunnable *> *readThreadQueue)
{
    auto dbg_PendingDeleteThread = &ReadThread::pendingDeleteThread;
    for (int i = 0; i < ReadThread::pendingDeleteThread.size(); ++i)
    {
        auto threadPointer = ReadThread::pendingDeleteThread[i];
        readThreadQueue->removeOne(threadPointer);
        delete threadPointer;
    }
    ReadThread::pendingDeleteThread.clear();
}

bool ReadFile::run_runThreadPool(int rescanInterval)
{
    using namespace Const_Core::Message;

    StdOut::printLine(Prefetching);

    // Create timer
    QElapsedTimer threadPoolTimer;
    threadPoolTimer.start();

    // Consume thread queue
    for (int i = 0; i < readThreadQueue.size(); ++i)
    {
        readThreadPool->start(readThreadQueue[i]);
    }

    // After thread done
    readThreadPool->waitForDone();

    // Get code execute time (only measure read, without other action)
    auto threadPoolTimeConsumed_miliseconds = threadPoolTimer.elapsed();
    auto threadPoolTimeConsumed_formatedString = Run_Timer::threadPoolTimeConsumed(threadPoolTimeConsumed_miliseconds);

    // Delete excluded file thread
    run_runThreadPool_DeleteExcludedFile(&readThreadQueue);

    // Run startup items
#if SKIP_STARTUP_ITEM == false
    Startup::startOnce();
#endif

    // Increase task count
    count_taskComplete++;

    // Idle, show execute time
    StdOut::print(Idle_Time);
    StdOut::print(threadPoolTimeConsumed_formatedString);
    StdOut::print(Idle_Sec);
    StdOut::printEndl();
    StdOut::flush();

    // Report execute result

    // No rescan interval founded
    if (rescanInterval <= 0)
    {
        // Reset count avoid int overflow
        count_taskComplete = 0;

        return true;
    }

    // Reach rescan interval
    if (count_taskComplete >= rescanInterval)
    {
        // Clear thread allocated memory
        for (int i = 0; i < readThreadQueue.size(); ++i)
        {
            delete readThreadQueue[i];
        }

        // Clear thread queue
        readThreadQueue.clear();

        // Reset count
        count_taskComplete = 0;

        return false;
    }
    // Not reach rescan interval
    else if (count_taskComplete < rescanInterval)
    {
        // Do nothing wait next loop
        return true;
    }

    // Default: Do nothing wait next loop
    return true;
}

void ReadFile::run_scanFolder_createReadFileThread_ququeThread(QString filePath)
{
    auto readThread = new ReadThread(filePath);
    ReadFile::readThreadQueue.append(readThread);
}

void ReadFile::run_scanFolder_createReadFileThread(QDir *prefetchFolder)
{
    prefetchFolder->setFilter(QDir::Files);
    auto subFileList = prefetchFolder->entryInfoList();

    for (int i = 0; i < subFileList.size(); ++i)
    {
        auto filePath = subFileList[i].absoluteFilePath();

        run_scanFolder_createReadFileThread_ququeThread(filePath);
    }
}

void ReadFile::run_scanFolder(QString prefetchFolderName)
{
    auto prefetchFolder = QDir(prefetchFolderName);

    // Get sub folder information

    // Cool stuff
    // Pass multiple at once
    // https://www.qtcentre.org/threads/22178-QDir-NoDotAndDotDot-hidding-all-files
    prefetchFolder.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    auto subFolderList = prefetchFolder.entryInfoList();
    auto subFolderListSize = subFolderList.size();

    if (subFolderListSize > 0)
    {
        for (int i = 0; i < subFolderListSize; ++i)
        {
            // Cool stuff
            // Even this is a folder
            // https://doc.qt.io/qt-5/qfileinfo.html#absoluteFilePath
            auto subFolderName = subFolderList[i].absoluteFilePath();

            // Save folder tree on stack but not read file immediately
            run_scanFolder(subFolderName);
        }
    }

    // Folder tree scan complete, create read file threads
    run_scanFolder_createReadFileThread(&prefetchFolder);
};

void ReadFile::run()
{
    using namespace Const_Core::Message;

    // Repeat root task loop
    while (true)
    {
        // Scan folder and queue threads that read each file

        StdOut::printLine(ScanFolder);

        for (int i = 0; i < prefetchFolders.size(); ++i)
        {
            auto prefetchFolderName = prefetchFolders[i];

            ReadFile::run_scanFolder(prefetchFolderName);
        }

        // Save current thread priority and restore later
        auto currentThreadPrioritySnapshot = QThread::currentThread()->priority();

        // Set thread priority
        // Only change priority while read files
        // No need to throttle cpu usage during scan folder
        QThread::currentThread()->setPriority(readThreadPriority);

        // Repeat read file loop
        // Once break, will rescan folder
        // If not break, simply repeat exist threads again
        while (true)
        {
            // Only enter read file loop if not pausing
            // If paused, skip this time and wait for next inerval
            if (ReadThread::pause == false)
            {
                bool runResult = run_runThreadPool(rescanInterval);
                if (runResult == false)
                {
                    // Wait for a while
                    Run_Sleep::sleep(prefetchIntervalInSecond);

                    // Trigger rescan
                    break;
                }
            }

            // Wait for a while
            Run_Sleep::sleep(prefetchIntervalInSecond);
        }

        // Restore thread priority
        QThread::currentThread()->setPriority(currentThreadPrioritySnapshot);
    }
}