#include <QString>

namespace Const_Core
{
    namespace Message
    {
        // read_file
        const QString ScanFolder = "Scan folder...";
        extern const QString CacheFound;
        const QString Prefetching = "Prefetching...";
        extern const QString Idle_Time;
        const QString Idle_Sec = " Sec";
        extern const QString ScanFolder_Time;
        extern const QString ScanFolder_Sec;
        const QString CodeExecuteTimeFormatter = "ss.zzz";
        const QString RescanIntervalReached1 = "Rescan interval reached.";
        extern const QString RescanIntervalReached2;

        // startup
        const QString RunStartupItems = "Run startup items...";
    }
    // Argc: count
    // Argi: index
    namespace Arg
    {
        const int IniArgc = 2;
        const int IniArgi = 1;
        const QString SkipStartup = "skipStartup";
        const QString ShowMainWindow = "showMainWindow";
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
