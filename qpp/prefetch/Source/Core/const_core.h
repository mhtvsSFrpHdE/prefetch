#include <QString>

namespace Const_Core
{
    namespace Message
    {
        // read_file
        const QString ScanFolder = "Scan folder...";
        extern const QString CacheFound;
        const QString Prefetching = "Prefetching...";
        const QString Idle_Time = "Idle, Time: ";
        const QString Idle_Sec = " Sec";
        const QString CodeExecuteTimeFormatter = "ss.zzz";
        const QString RescanIntervalReached1 = "Rescan interval reached.";
        extern const QString RescanIntervalReached2;

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
        const QString MetaData = "MetaData";
        const QString ScanFolder = "ScanFolder";
    }

    namespace MetaData_ConfigKeyName
    {
        const QString Size = "Size";
    }
}
