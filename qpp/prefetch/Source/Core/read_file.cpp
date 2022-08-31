#include <QThread>
#include <QElapsedTimer>
#include <QTime>

#include "read_file.h"
#include "..\Setting\setting.h"
#include "..\Output\stdout.h"
#include "Thread\read_thread.h"
#include "startup.h"

SleepThread *ReadFile::sleepThreadAddress = new SleepThread();
int ReadFile::count_start_scanFolder = 0;
QList<QRunnable *> ReadFile::readThreadQueue = QList<QRunnable *>();
QThreadPool *ReadFile::readThreadPool = QThreadPool::globalInstance();
int ReadFile::count_taskComplete = 0;
// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, QThread::Priority> ReadFile::priorityMap(
    std::map<QString, QThread::Priority>{
        {"IdlePriority", QThread::IdlePriority},
        {"LowestPriority", QThread::LowestPriority},
        {"LowPriority", QThread::LowPriority},
        {"NormalPriority", QThread::NormalPriority},
        {"HighPriority", QThread::HighPriority},
        {"HighestPriority", QThread::HighestPriority},
        {"TimeCriticalPriority", QThread::TimeCriticalPriority},
        {"InheritPriority", QThread::InheritPriority}});

// Wrapper to access QThread functions
class start_ReadSleep
{
public:
    static void sleep(unsigned long secs)
    {
        ReadFile::sleepThreadAddress->sleepTimeInSeconds = secs;

        ReadFile::sleepThreadAddress->start();
        ReadFile::sleepThreadAddress->wait();
    }

private:
    // Disallow creating an instance of this object
    start_ReadSleep();
};

void ReadFile::run()
{
    // Get and set thread number
    auto getThreadNumber = Setting::getInt("Thread", "MaxThreadCount", Setting::setting);
    if (getThreadNumber.success && getThreadNumber.result >= 1)
    {
        readThreadPool->setMaxThreadCount(getThreadNumber.result);
    }

    // Get prefetch folder
    auto prefetchFolders = Setting::getArray("PrefetchFolder", Setting::setting);

    // Get exclude folder
    auto excludeFolders = Setting::getArray("ExcludeFolder", Setting::setting);
    for (int i = 0; i < excludeFolders.size(); ++i)
    {
        auto excludeFolderName = QDir(excludeFolders[i]).absolutePath();
        ReadThread::excludeFolders.append(excludeFolderName);
    }

    // Get priority include search patterns
    auto priorityIncludePatterns = Setting::getArray("PriorityIncludePattern", Setting::setting);
    for (int i = 0; i < priorityIncludePatterns.size(); ++i)
    {
        auto priorityIncludePattern = priorityIncludePatterns[i];
        ReadThread::priorityIncludePatterns.append(priorityIncludePattern);
    }

    // Get rescan interval
    auto getRescanInterval = Setting::getInt("Thread", "RescanInterval", Setting::setting);

    // Get prefetch interval
    auto getPrefetchInterval = Setting::getUnsignedLong("Thread", "PrefetchInterval", Setting::setting);
    unsigned long prefetchIntervalInSecond = getPrefetchInterval.result;

    // Get read thread priority
    auto getReadThreadPriority = Setting::getString("Thread", "ReadThreadPriority", Setting::setting);
    QThread::Priority readThreadPriority = priorityMap[getReadThreadPriority];

    // Set do not auto delete for thread instance
    ReadThread::autoDeletePreset = false;

    // Repeat root task loop
    while (true)
    {
        // Scan folder and queue threads that read each file

        StdOut::printLine("Scan folder...");

        for (int i = 0; i < prefetchFolders.size(); ++i)
        {
            auto prefetchFolderName = prefetchFolders[i];

            ReadFile::start_scanFolder(prefetchFolderName);
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
                bool runResult = start_runThreadPool(getRescanInterval.result);
                if (runResult == false)
                {
                    // Wait for a while
                    start_ReadSleep::sleep(prefetchIntervalInSecond);

                    // Trigger rescan
                    break;
                }
            }

            // Wait for a while
            start_ReadSleep::sleep(prefetchIntervalInSecond);
        }

        // Restore thread priority
        QThread::currentThread()->setPriority(currentThreadPrioritySnapshot);
    }
}

void ReadFile::start_createReadFileThread_ququeThread(QString filePath)
{
    auto readThread = new ReadThread(filePath);
    ReadFile::readThreadQueue.append(readThread);
}

void ReadFile::start_createReadFileThread(QDir *prefetchFolder)
{
    prefetchFolder->setFilter(QDir::Files);
    auto subFileList = prefetchFolder->entryInfoList();

    for (int i = 0; i < subFileList.size(); ++i)
    {
        auto filePath = subFileList[i].absoluteFilePath();

        start_createReadFileThread_ququeThread(filePath);
    }
}

void ReadFile::start_scanFolder(QString prefetchFolderName)
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
            start_scanFolder(subFolderName);
        }
    }

    // Folder tree scan complete, create read file threads
    start_createReadFileThread(&prefetchFolder);
};

bool ReadFile::start_runThreadPool(int rescanInterval)
{
    StdOut::printLine("Prefetching...");

    // Create timer
    QElapsedTimer threadPoolTimer;
    threadPoolTimer.start();

    // Consume thread queue
    for (int i = 0; i < readThreadQueue.size(); ++i)
    {
        readThreadPool->start(readThreadQueue[i]);
    }

    // Delete excluded file thread
    readThreadPool->waitForDone();

    auto dbg_PendingDeleteThread = &ReadThread::pendingDeleteThread;
    for (int i = 0; i < ReadThread::pendingDeleteThread.size(); ++i)
    {
        auto threadPointer = ReadThread::pendingDeleteThread[i];
        readThreadQueue.removeOne(threadPointer);
        delete threadPointer;
    }
    ReadThread::pendingDeleteThread.clear();

    // Get code execute time
    auto threadPoolTimeConsumedMiliseconds = threadPoolTimer.elapsed();
    auto threadPoolTimeConsumedFormatedString = QTime()
                                                    .addMSecs(threadPoolTimeConsumedMiliseconds)
                                                    .toString("ss.zzz");
    threadPoolTimeConsumedFormatedString.chop(1);

    // Run startup items
#if SKIP_STARTUP_ITEM == false
    Startup::startOnce();
#endif

    // Increase task count
    count_taskComplete++;

    StdOut::print("Idle, Time: ");
    StdOut::print(threadPoolTimeConsumedFormatedString);
    StdOut::print(" Sec");
    StdOut::printEndl();
    StdOut::flush();

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
