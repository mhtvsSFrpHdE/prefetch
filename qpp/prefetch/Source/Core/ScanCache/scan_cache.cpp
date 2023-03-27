#include <QFileInfo>
#include <QApplication>

#include "scan_cache.h"
#include "../ReadFile/read_file_thread.h"
#include "../../Setting/setting.h"
#include "../const_core.h"
#include "../../Global/global.h"

QSettings *Core_ScanCache::cache = NULL;
QString Core_ScanCache::cacheFilePath = NULL;
bool Core_ScanCache::cacheFileExist = false;

bool Core_ScanCache::init_cacheFileExist()
{
    auto cacheFile = QFileInfo(cacheFilePath);
    return cacheFile.exists();
}

void Core_ScanCache::init()
{
    // Cache file path default value
    cacheFilePath = Const_Cache::DefaultCacheFilePath;

    // Get cache file path
    cacheFilePath = Global::commandLineArgumentAddress->getScanCacheFilePath();
    cacheFilePath = QApplication::applicationDirPath() + Const_Cache::PathSplitter() + cacheFilePath;
    cacheFileExist = init_cacheFileExist();

    // Read ini from exe stored folder
    cache = new QSettings(cacheFilePath, QSettings::IniFormat);
}

void Core_ScanCache::saveScanCache(QList<QRunnable *> *readThreadQueueAddress, bool override)
{
    // Override
    bool skipExist = override == false;
    if (skipExist && cacheFileExist)
    {
        return;
    }

    using namespace Const_Cache::ConfigGroupName;
    using namespace Const_Cache::MetaData_ConfigKeyName;

    // Clear exist cache
    cache->remove(ScanFolder);

    // Snapshot current thread pool
    auto readThreadQueue = *readThreadQueueAddress;
    Setting_setArray_macro(ScanFolder, readThreadQueue, readThreadQueue.size(), Core_ReadFileThread *, item->filePath, cache);

    // Save metadata
    Setting::setValue(MetaData, Size, QString::number(readThreadQueue.size()), cache);

    // Mark cache exist after save
    cacheFileExist = true;
}

void Core_ScanCache::loadScanCache(QList<QRunnable *> *readThreadQueueAddress)
{
    using namespace Const_Cache::ConfigGroupName;
    using namespace Const_Cache::MetaData_ConfigKeyName;

    auto getSize = Setting::getInt(MetaData, Size, cache);
    auto size = getSize.result;

#define valueCallback(foo) Core::run_scanFolder_createReadFileThread_ququeThread(foo, true)
    Setting_getOrderedArrayValue_macro(ScanFolder, size, valueCallback, cache);
}

void Core_ScanCache::expireCache()
{
    cacheFileExist = false;
}
