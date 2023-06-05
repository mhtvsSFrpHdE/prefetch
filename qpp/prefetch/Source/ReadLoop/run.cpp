#include <QElapsedTimer>

#include "read_loop.h"
#include "const_read_loop.h"
#include "../Output/stdout.h"
#include "ReadFile/read_file_thread.h"
#include "Sleep/sleep.h"
#include "Startup/startup.h"
#include "ScanCache/scan_cache.h"
#include "Time/time.h"
#include "../Output/log.h"
#include "Skip/skip.h"
#include "../Example/semaphore_example.h"
#include "RocketLaunch/rocket_launch.h"

void run_runThreadPool_DeleteExcludedFile(QList<QRunnable *> *readThreadQueueAddress)
{
    ReadLoop_ReadFileThread::pendingDeleteThreadMutex.lock();
    for (int i = 0; i < ReadLoop_ReadFileThread::pendingDeleteThread.size(); ++i)
    {
        auto threadPointer = ReadLoop_ReadFileThread::pendingDeleteThread[i];
        readThreadQueueAddress->removeOne(threadPointer);
        delete threadPointer;
    }
    ReadLoop_ReadFileThread::pendingDeleteThread.clear();
    ReadLoop_ReadFileThread::pendingDeleteThreadMutex.unlock();
}

bool ReadLoop::run_runThreadPool(int rescanInterval)
{
    using namespace Const_ReadLoop::Message;

    StdOut::printLine(Prefetching);

    // Create timer
    QElapsedTimer threadPoolTimer;
    threadPoolTimer.start();

    // Allocate RAM
    (*ReadLoop_ReadFileThread::newSharedReadBuffer_action)();

    // Consume thread queue
    for (int i = 0; i < readThreadQueue.size(); ++i)
    {
        readThreadPool->start(readThreadQueue[i]);
    }

    // After thread done
    readThreadPool->waitForDone();

    // Release RAM
    (*ReadLoop_ReadFileThread::deleteSharedReadBuffer_action)();

    // Get code execute time (only measure read, without other action)
    auto threadPoolTimeConsumed_miliseconds = threadPoolTimer.elapsed();
    auto threadPoolTimeConsumed_formatedString = ReadLoop_Time::timeConsumed(threadPoolTimeConsumed_miliseconds);

    // Delete excluded file thread
    run_runThreadPool_DeleteExcludedFile(&readThreadQueue);

    // Save scan cache
    ReadLoop_ScanCache::saveScanCache(&readThreadQueue);

    // Run startup items
#if SKIP_STARTUP_ITEM == false
    (*ReadLoop_Startup::startOnce)();
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

void ReadLoop::run_scanFolder_createReadFileThread_ququeThread(QString filePath, bool skipSearch)
{
    auto readThread = new ReadLoop_ReadFileThread(filePath, skipSearch);

    ReadLoop::readThreadQueue.append(readThread);
}

void ReadLoop::run_scanFolder_createReadFileThread(QDir *prefetchFolder)
{
    prefetchFolder->setFilter(QDir::Files);
    auto subFileList = prefetchFolder->entryInfoList();

    for (int i = 0; i < subFileList.size(); ++i)
    {
        auto filePath = subFileList[i].absoluteFilePath();

        run_scanFolder_createReadFileThread_ququeThread(filePath);
    }
}

void ReadLoop::run_scanFolder(QString prefetchFolderName)
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

void ReadLoop::run()
{
    using namespace Const_ReadLoop::Message;

    typedef ReadLoop_ReadFileThread crft;
    typedef SemaphoreExample se;

    init();

    // Set thread priority
    QThread::currentThread()->setPriority(readThreadPriority);

    // Repeat root task loop
    while (true)
    {
        // Scan folder and queue threads that read each file

        // Create timer
        QElapsedTimer scanFolderTimer;
        scanFolderTimer.start();

        StdOut::printLine(ScanFolder);

        // If scan cache available, skip parse prefetch folder
        if (ReadLoop_ScanCache::cacheFileExist)
        {
            StdOut::printLine(CacheFound);
            ReadLoop_ScanCache::loadScanCache(&readThreadQueue);
        }
        else
        {
            for (int i = 0; i < prefetchFolders.size(); ++i)
            {
                auto prefetchFolderName = prefetchFolders[i];

                ReadLoop::run_scanFolder(prefetchFolderName);
            }
        }

        // Get code execute time (only measure read, without other action)
        auto scanFolderTimeConsumed_miliseconds = scanFolderTimer.elapsed();
        auto scanFolderTimeConsumed_formatedString = ReadLoop_Time::timeConsumed(scanFolderTimeConsumed_miliseconds);

        // Scan complete, show execute time
        StdOut::print(ScanFolder_Time);
        StdOut::print(scanFolderTimeConsumed_formatedString);
        StdOut::print(ScanFolder_Sec);
        StdOut::printEndl();
        StdOut::flush();

        // Repeat read file loop
        // Once break, will rescan folder
        // If not break, simply repeat exist threads again
        while (true)
        {
            // Check point

            // Lock stop mutex
            //
            // If mutex unavailable, block will happen until mutex available
            LAST_KNOWN_POSITION(3)
            se::lock(crft::stopSemaphore);

            // Release stop mutex
            //
            // Lock mutex is for being block
            // Since block already done, no need to keep mutex on hand
            LAST_KNOWN_POSITION(4)
            se::unlock(crft::stopSemaphore);

            bool checkProcess = ReadLoop_Skip::check();
            if (checkProcess == false)
            {
                // Report skip process detected
                StdOut::printLine(SkipProcessDetected);

                // Wait for prefetch interval
                ReadLoop_Sleep::sleep();

                // Skip
                continue;
            }

            // Activate thread pool and wait result
            bool runResult = run_runThreadPool(rescanInterval);

            // Thread pool report rescan required
            if (runResult == false)
            {
                // Report rescan interval reached
                StdOut::printLine(RescanIntervalReached1);
                StdOut::printLine(RescanIntervalReached2);

                // Expire cache
                ReadLoop_ScanCache::expireCache();

                // Wait for prefetch interval
                ReadLoop_Sleep::sleep();

                // Exit while loop, trigger rescan
                break;
            }

            // Rocket launch
            (*ReadLoop_RocketLaunch::rocketLaunch_action)();

            // Wait for prefetch interval
            ReadLoop_Sleep::sleep();
        }
    }
}
