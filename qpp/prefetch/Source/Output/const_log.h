#ifndef Const_Log_h
#define Const_Log_h

#include <QString>

namespace Const_Log
{
    const QString DefaultLogFilePath = "prefetch.log";
    const QString DefaultLogFilePathSuffix = ".log";
    extern QString PathSplitter;

    namespace Message
    {
        extern QString NewLine;
        extern QString Tab;

        extern QString LastKnownLocation_BEGIN;
        extern QString LastKnownLocation_END;
        extern QString LastKnownLocation_INLINE;
        extern QString LastKnownLocation_LOCK;
        extern QString LastKnownLocation_UNLOCK;
        extern QString File;
        extern QString Function;
        extern QString Line;

        extern void init();
    }

    enum LastKnownLocationEnum
    {
        BEGIN = 0,
        END = 1,
        INLINE = 2,
        // You can't print if deadlock already occurs
        LOCK = 3,
        // Print before certain unlock no guarantee is unlocked
        UNLOCK = 4
    };
}
#endif
