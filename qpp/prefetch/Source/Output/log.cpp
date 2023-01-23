#include <QFileInfo>
#include <QApplication>

#include "log.h"
#include "..\Setting\setting.h"
#include "..\Core\const_core.h"
#include "..\Example\mutex_example.h"

QString Log::logFilePath;
QFile *Log::logFile;
QTextStream *Log::logTextStream;
QMutex *Log::logMutex = MutexExample::getLockedMutex();

Setting::GetGenericResult<QString> init_getLogFilePath(int argc, QStringList argv)
{
    using namespace Const_Core;

    Setting::GetGenericResult<QString> getLogFilePath;

    bool argcNotEnough = argc < Arg::IniArgc;
    if (argcNotEnough)
    {
        getLogFilePath.success = false;
        return getLogFilePath;
    }

    // Watch out! This one can crash if argc check not pass
    // First argument is not alternative setting ini, ignore
    bool firstArgIsBoolFlag = argv[1].startsWith(Arg::BoolFlagBeginWith);
    if (firstArgIsBoolFlag)
    {
        getLogFilePath.success = false;
        return getLogFilePath;
    }

    auto settingFile = QFileInfo(argv[1]);
    QString logFileName = settingFile.baseName() + Const_Log::DefaultLogFilePathSuffix;

    getLogFilePath.result = logFileName;
    return getLogFilePath;
}

void Log::init(int argc, QStringList argv)
{
    // Log file path default value
    logFilePath = Const_Log::DefaultLogFilePath;

    // Get log file path
    auto getLogFilePath = init_getLogFilePath(argc, argv);
    if (getLogFilePath.success)
    {
        logFilePath = getLogFilePath.result;
    }
    logFilePath = QApplication::applicationDirPath() + Const_Log::PathSplitter + logFilePath;

    // Open log file
    logFile = new QFile(logFilePath);
    logFile->open(QIODevice::WriteOnly);

    // Bind text stream to log file
    logTextStream = new QTextStream(logFile);

    // Unlock logMutex
    unlock();
}

void Log::lock()
{
    logMutex->lock();
}

void Log::unlock()
{
    logMutex->unlock();
}

void Log::shutdown()
{
    logFile->close();
}
