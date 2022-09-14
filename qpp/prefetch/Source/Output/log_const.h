#include <QString>

namespace Const_Log
{
    const QString DefaultLogFilePath = "prefetch.log";
    const QString DefaultLogFilePathSuffix = ".log";
    extern const QString PathSplitter;

    namespace Message
    {
        extern const QString NewLine;
        extern const QString Tab;

        const QString LastKnownLocation_BEGIN = "LastKnownLocation BEGIN\n";
        const QString LastKnownLocation_END = "LastKnownLocation END\n";
        const QString LastKnownLocation_INLINE = "LastKnownLocation INLINE\n";
        extern const QString File;
        extern const QString Function;
        extern const QString Line;
    }

    enum LastKnownLocationEnum
    {
        BEGIN = 0,
        END = 1,
        INLINE = 2
    };
}
