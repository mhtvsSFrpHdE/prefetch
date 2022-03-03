#include <QThreadPool>
#include <QStringList>
#include <QDir>

// Static class
class ReadFile
{
public:
    // Start read file
    static void start();

    // Any init code
    static void init();

private:
    // Disallow creating an instance of this object
    ReadFile() {}

    static int count_start_scanFolder;
    static QList<QRunnable *> readThreadQueue;
    static QThreadPool *readThreadPool;

    // Queue thread for later use
    // Start threadpool after iterate complete to reduce I/O fragment
    static void start_createReadFileThread_ququeThread(QString filePath);

    // Read all file in QFileInfoList
    static void start_createReadFileThread(QDir *prefetchFolder);

    // Iterated function
    static void start_scanFolder(QString prefetchFolderName);

    // Consume thread queue and empty queue after done
    static void start_runThreadPool();
};
