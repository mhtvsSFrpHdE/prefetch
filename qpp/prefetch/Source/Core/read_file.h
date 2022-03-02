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
    static void start_readFile_ququeThread(QString filePath);

    // Read all file in QFileInfoList
    static void start_readFile(QDir *prefetchFolder);

    // iterated function
    static void start_scanFolder(QString prefetchFolderName);
    static void start_runThread();
};
