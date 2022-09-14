#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>

#include "..\Define\define.h"

// Automatically lock and unlock log mutex
#if LOG_ENABLED

#define IF_LOG_ENABLED(code) \
    {                        \
        Log::lock();         \
        code                 \
        Log::unlock();       \
    }

#else

#define IF_LOG_ENABLED(code)

#endif

// Static class
class Log
{
public:
    static QString logFilePath;
    static QFile *logFile;
    static QTextStream *logTextStream;
    static void init(int argc, QStringList argv);

    // Log takes time to initialized
    //     However, a stdout may occur before Log has initialized
    //     Use mutex to delay the print request
    static QMutex *logMutex;

    // Wrap access to logMutex
    static void lock();

    // Wrap access to logMutex
    static void unlock();

private:
    static QMutex *getLockedMutex();

    // Disallow creating an instance of this object
    Log() {}
};
