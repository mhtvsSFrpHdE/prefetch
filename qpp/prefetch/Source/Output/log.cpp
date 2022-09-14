#include <QFileInfo>
#include <QApplication>

#include "log.h"
#include "..\Setting\setting.h"
#include "log_const.h"

QString Log::logFilePath;
QFile *Log::logFile;
QTextStream *Log::logTextStream;
QMutex *Log::logMutex = getLockedMutex();

QMutex *Log::getLockedMutex()
{
    auto mutexAddress = new QMutex(QMutex::NonRecursive);
    mutexAddress->lock();
    return mutexAddress;
}

Setting::GetGenericResult<QString> init_getLogFilePath(int argc, QStringList argv)
{
    Setting::GetGenericResult<QString> getLogFilePath;

    if (argc != 2)
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
    logMutex->unlock();
}

void Log::lock()
{
    logMutex->lock();
}

void Log::unlock()
{
    logMutex->unlock();
}
