#ifndef Const_Log_h
#define Const_Log_h

#include <QString>

// This file should independently to others
// Log must always available
namespace Const_Log
{
    const QString DefaultLogFilePath = "prefetch.log";
    const QString DefaultLogFilePathSuffix = ".log";
    const QString PathSplitter = "/";

    namespace Message
    {
        const QString NewLine = "\n";
        const QString Tab = "    ";

        const QString LastKnownLocation_BEGIN = "LastKnownLocation BEGIN\n";
        const QString LastKnownLocation_END = "LastKnownLocation END\n";
        const QString LastKnownLocation_INLINE = "LastKnownLocation INLINE\n";
        const QString LastKnownLocation_LOCK = "LastKnownLocation LOCK\n";
        const QString LastKnownLocation_UNLOCK = "LastKnownLocation UNLOCK\n";
        extern const QString File;
        extern const QString Function;
        extern const QString Line;
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
