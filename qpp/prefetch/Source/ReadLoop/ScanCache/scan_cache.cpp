#include <QFileInfo>
#include <QApplication>
#include <QMessageBox>

#include "scan_cache.h"
#include "../ReadFile/read_file_thread.h"
#include "../../Setting/setting.h"
#include "../../Setting/const_setting.h"
#include "../const_read_loop.h"
#include "../../Global/global.h"
#include "../../Output/stdout.h"
#include "../../Example/exception_example.h"
#include "../../Output/log.h"

#define gn Const_Cache::ConfigGroupName
#define mkn Const_Cache::MetaData_ConfigKeyName
#define mcv Const_Cache::Value::MetaData

QSettings *ReadLoop_ScanCache::cache = NULL;
QString ReadLoop_ScanCache::cacheFilePath = NULL;
bool ReadLoop_ScanCache::cacheFileExist = false;

bool ReadLoop_ScanCache::init_cacheFileExist()
{
    auto cacheFile = QFileInfo(cacheFilePath);
    return cacheFile.exists();
}

void ReadLoop_ScanCache::init()
{
    // Cache file path default value
    cacheFilePath = Const_Cache::DefaultCacheFilePath;

    // Get cache file path
    cacheFilePath = Global::commandLineArgumentAddress->getScanCacheFilePath();
    cacheFilePath = QApplication::applicationDirPath() + Const_Cache::PathSplitter() + cacheFilePath;
    cacheFileExist = init_cacheFileExist();

    // Read ini from exe stored folder
    cache = new QSettings(cacheFilePath, QSettings::IniFormat);

    // Check config version
    // Newly created config will always have config version, if cache file NOT exist, ignore this check
    bool configVersionExist = cacheFileExist == false || Global::qSettingInterfaceAddress->getExist(gn::MetaData, mkn::ConfigVersion, cache);
    if (configVersionExist == false)
    {
        using namespace Const_Setting::Exception;

        QString exception = IncompatibleConfigVersion;
        QString exceptionUiText = exception + IncompatibleConfigVersion_UI + cacheFilePath;
        LAST_KNOWN_POSITION(2)
        ExceptionExample::throwException(exception, exceptionUiText);
    }
}

void ReadLoop_ScanCache::saveScanCache(QList<QRunnable *> *readThreadQueueAddress, bool override)
{
    // Override
    bool skipExist = override == false;
    if (skipExist && cacheFileExist)
    {
        return;
    }

    // Clear exist cache
    cache->remove(gn::ScanFolder);

    // Snapshot current thread pool
    auto readThreadQueue = *readThreadQueueAddress;
    Setting_setArray_macro(gn::ScanFolder, readThreadQueue, readThreadQueue.size(), ReadLoop_ReadFileThread *, item->filePath, cache);

    // Save metadata
    Setting::setValue(gn::MetaData, mkn::Size, QString::number(readThreadQueue.size()), cache);
    Setting::setValue(gn::MetaData, mkn::ConfigVersion, QString::number(mcv::ConfigVersion), cache);

    // Mark cache exist after save
    cacheFileExist = true;
}

void ReadLoop_ScanCache::loadScanCache(QList<QRunnable *> *readThreadQueueAddress)
{
    using namespace Const_Cache::ConfigGroupName;
    using namespace Const_Cache::MetaData_ConfigKeyName;

    auto getSize = Setting::getInt(MetaData, Size, cache);
    auto size = getSize.result;

#define valueCallback(foo) ReadLoop::run_scanFolder_createReadFileThread_ququeThread(foo, true)
    Setting_getOrderedArrayValue_macro(ScanFolder, size, valueCallback, cache);
}

void ReadLoop_ScanCache::expireCache()
{
    cacheFileExist = false;
}
