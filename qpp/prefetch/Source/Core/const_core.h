#include <QString>

namespace Const_Core
{
    namespace Message
    {
        // read_file
        const QString ScanFolder = "Scan folder...";
        const QString Prefetching = "Prefetching...";
        const QString Idle_Time = "Idle, Time: ";
        const QString Idle_Sec = " Sec";
        const QString CodeExecuteTimeFormatter = "ss.zzz";

        // startup
        const QString RunStartupItems = "Run startup items...";
    }
}

namespace Const_Cache
{
    const QString DefaultCacheFilePath = "prefetch.cache.ini";
    const QString DefaultCacheFilePathSuffix = ".cache.ini";
    extern const QString PathSplitter;

    namespace ConfigGroupName
    {
        const QString ScanFolder = "ScanFolder";
    }
}
