#include <QThreadPool>
#include <QStringList>
#include <QDir>
#include <QMap>

#include "..\Thread\sleep_thread.h"

class ReadFile : public QThread
{
public:
    ReadFile() {}

    // Start read file
    // while(true), do not run directly on main thread
    void run() override;

    // Queue thread for later use
    // Start threadpool after iterate complete to reduce I/O fragment
    static void run_scanFolder_createReadFileThread_ququeThread(QString filePath);

    // Save running sleep thread address for later access on other thread
    static SleepThread *sleepThreadAddress;

    // Shortcut to default thread pool
    static QThreadPool *readThreadPool;

private:
    // Setting ReadThreadPriority
    QThread::Priority readThreadPriority;
    // Setting RescanInterval
    int rescanInterval;
    // Setting PrefetchInterval
    unsigned long prefetchIntervalInSecond;

    // Read config file
    void init();

    // How many times entered run_scanFolder function
    // Help identify iterate problems
    static int count_start_scanFolder;

    // Created QRunnable object pointers
    static QList<QRunnable *> readThreadQueue;

    // How many times all thread done
    // Before start a new task, if this value equals to RescanInterval
    // Clean previous created thread and rescan folder to create new
    static int count_taskComplete;

    // Convert config file option to QT thread enum
    static QMap<QString, QThread::Priority> priorityMap;

        // Read all file in QFileInfoList
    static void run_scanFolder_createReadFileThread(QDir *prefetchFolder);

    // Iterated function
    static void run_scanFolder(QString prefetchFolderName);

    // Consume thread queue
    //     and empty queue after done if reach rescan interval
    // Return
    //     true: No need to rescan folder
    //     false: Reached rescan interval, must rescan folder
    static bool run_runThreadPool(int rescanInterval);

    QStringList prefetchFolders;
};
