#include <QThread>
#include <QElapsedTimer>
#include <QTime>

#include "read_file.h"
#include "..\Setting\setting.h"
#include "..\Output\stdout.h"
#include "Thread\read_thread.h"
#include "startup.h"

SleepThread *ReadFile::sleepThreadAddress;
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
        SleepThread sleepThread(secs);
        ReadFile::sleepThreadAddress = &sleepThread;

        sleepThread.start();
        sleepThread.wait();
    }

private:
    // Disallow creating an instance of this object
    start_ReadSleep();
};

void ReadFile::start()
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
    unsigned long prefetchIntervalInSecond = 60;
    if (getPrefetchInterval.success && getPrefetchInterval.result > 0)
    {
        prefetchIntervalInSecond = getPrefetchInterval.result;
    }

    // Get read thread priority
    auto getReadThreadPriority = Setting::getString("Thread", "ReadThreadPriority", Setting::setting);
    QThread::Priority readThreadPriority = priorityMap[getReadThreadPriority];

    // Set do not auto delete for thread instance
    ReadThread::autoDeletePreset = false;

    // Repeat root task loop
    while (true)
    {
        // Scan folder and queue threads that read each file

        *StdOut::consoleOutput << "Scan folder..."
                               << endl;
        StdOut::consoleOutput->flush();

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
            bool runResult = start_runThreadPool(getRescanInterval.result);
            if (runResult == false)
            {
                // Wait for a while
                start_ReadSleep::sleep(prefetchIntervalInSecond);

                break;
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

    auto rescanInterval = Setting::getInt("Thread", "RescanInterval", Setting::setting);
    if (rescanInterval.success && rescanInterval.result > 0)
    {
        readThread->setAutoDelete(false);
    }

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
    // ReadFile::count_start_scanFolder++;
    // *StdOut::consoleOutput << "Enter start_scanFolder times: "
    //                        << ReadFile::count_start_scanFolder
    //                        << endl;

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
    *StdOut::consoleOutput << "Prefetching..."
                           << endl;
    StdOut::consoleOutput->flush();

    // Create timer
    QElapsedTimer threadPoolTimer;
    threadPoolTimer.start();

    // Consume thread queue
    for (int i = 0; i < readThreadQueue.size(); ++i)
    {
        readThreadPool->start(readThreadQueue[i]);
    }

    readThreadPool->waitForDone();

    // Get code execute time
    auto threadPoolTimeConsumedMiliseconds = threadPoolTimer.elapsed();
    auto threadPoolTimeConsumedFormatedString = QTime()
                                                    .addMSecs(threadPoolTimeConsumedMiliseconds)
                                                    .toString("ss.zzz");
    threadPoolTimeConsumedFormatedString.chop(1);

    // Run startup items
    Startup::startOnce();

    // Increase task count
    count_taskComplete++;

    *StdOut::consoleOutput << "Idle, Time: "
                           << threadPoolTimeConsumedFormatedString
                           << " Sec"
                           << endl;
    StdOut::consoleOutput->flush();

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
}
