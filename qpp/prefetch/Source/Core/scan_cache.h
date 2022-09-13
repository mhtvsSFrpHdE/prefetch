#include <QList>
#include <QRunnable>
#include <QSettings>

// Static class
class ScanCache
{
public:
    static QSettings *cache;

    static void init(int argc, QStringList argv);

    static void saveScanCache(QList<QRunnable *> *readThreadQueueAddress);

    static bool cacheFileExist;

private:
    // Disallow creating an instance of this object
    ScanCache() {}
};
