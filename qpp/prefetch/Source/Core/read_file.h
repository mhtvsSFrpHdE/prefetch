#include <QThreadPool>
#include <QStringList>
#include <QDir>

#include "Thread\sleep_thread.h"

// Static class
class ReadFile
{
public:
    // Start read file
    // while(true)
    static void start();

    // Save running sleep thread address for later access on other thread
    static SleepThread* sleepThreadAddress;

private:
    // Disallow creating an instance of this object
    ReadFile() {}

    // How many times entered start_scanFolder function
    // Help identify iterate problems
    static int count_start_scanFolder;

    // Created QRunnable object pointers
    static QList<QRunnable *> readThreadQueue;

    // Shortcut to default thread pool
    static QThreadPool *readThreadPool;

    // How many times all thread done
    // Before start a new task, if this value equals to RescanInterval
    // Clean previous created thread and rescan folder to create new
    static int count_taskComplete;

    // Convert config file option to QT thread enum
    static QMap<QString, QThread::Priority> priorityMap;

    // Queue thread for later use
    // Start threadpool after iterate complete to reduce I/O fragment
    static void start_createReadFileThread_ququeThread(QString filePath);

    // Read all file in QFileInfoList
    static void start_createReadFileThread(QDir *prefetchFolder);

    // Iterated function
    static void start_scanFolder(QString prefetchFolderName);

    // Consume thread queue and empty queue after done
    // Return
    //     true: No need to rescan folder
    //     false: Reached rescan interval, must rescan folder
    static bool start_runThreadPool(int rescanInterval);
};
