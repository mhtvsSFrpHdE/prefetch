#include <QList>
#include <QRunnable>
#include <QSettings>

class ScanCache
{
public:
    static QSettings *cache;

    // Init code: check cache file exist
    static bool init_cacheFileExist();
    // Any init code
    static void init();

    // Snapshot current thread pool to cache file
    static void saveScanCache(QList<QRunnable *> *readThreadQueueAddress, bool override = false);

    // Restore thread pool from cache file
    static void loadScanCache(QList<QRunnable *> *readThreadQueueAddress);

    // Tell cache expired
    static void expireCache();

    static QString cacheFilePath;
    static bool cacheFileExist;
};
