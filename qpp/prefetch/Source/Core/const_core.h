#ifndef Const_Core_h
#define Const_Core_h

#include <QString>

namespace Const_Core
{
    namespace Message
    {
        // read_file
        extern QString ScanFolder;
        extern QString CacheFound;
        extern QString Prefetching;
        extern QString Idle_Time;
        extern QString Idle_Sec;
        extern QString ScanFolder_Time;
        extern QString ScanFolder_Sec;
        extern QString CodeExecuteTimeFormatter;
        extern QString RescanIntervalReached1;
        extern QString RescanIntervalReached2;

        // startup
        extern QString RunStartupItems;

        extern void init();

        // See translate_define.h for more information
        extern void tdummy();
    }
    // Argc: count
    // Argi: index
    namespace Arg
    {
        // Assume index 0 is application.exe path
        const int ArgBeginIndex = 1;
        const int IniArgc = 2;
        const int IniArgi = 1;
        const QString BoolFlagBeginWith = "-";
        const QString SkipStartup = "skipStartup";
        const QString ShowMainWindow = "showMainWindow";
    }
}

namespace Const_Cache
{
    const QString DefaultCacheFilePath = "prefetch.cache.ini";
    const QString DefaultCacheFilePathSuffix = ".cache.ini";
    extern QString PathSplitter;

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

#endif
