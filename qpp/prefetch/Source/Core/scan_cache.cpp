#include <QFileInfo>
#include <QApplication>

#include "scan_cache.h"
#include "Thread\Read\read_thread_crtrt.h"
#include "..\Setting\setting.h"
#include "const_core.h"
#include "ReadFile\read_file.h"
#include "..\Global\global.h"

QSettings *ScanCache::cache = NULL;
QString ScanCache::cacheFilePath = NULL;
bool ScanCache::cacheFileExist = false;

bool ScanCache::init_cacheFileExist()
{
    auto cacheFile = QFileInfo(cacheFilePath);
    return cacheFile.exists();
}

void ScanCache::init()
{
    // Cache file path default value
    cacheFilePath = Const_Cache::DefaultCacheFilePath;

    // Get cache file path
    cacheFilePath = Global::commandLineArgumentAddress->getScanCacheFilePath();
    cacheFilePath = QApplication::applicationDirPath() + Const_Cache::PathSplitter + cacheFilePath;
    cacheFileExist = init_cacheFileExist();

    // Read ini from exe stored folder
    cache = new QSettings(cacheFilePath, QSettings::IniFormat);
}

void ScanCache::saveScanCache(QList<QRunnable *> *readThreadQueueAddress, bool override)
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
    Setting_setArray_macro(ScanFolder, readThreadQueue, readThreadQueue.size(), ReadThread *, item->filePath, cache);

    // Save metadata
    Setting::setValue(MetaData, Size, QString::number(readThreadQueue.size()), cache);

    // Mark cache exist after save
    cacheFileExist = true;
}

void ScanCache::loadScanCache(QList<QRunnable *> *readThreadQueueAddress)
{
    using namespace Const_Cache::ConfigGroupName;
    using namespace Const_Cache::MetaData_ConfigKeyName;

    auto getSize = Setting::getInt(MetaData, Size, cache);
    auto size = getSize.result;

#define valueCallback(foo) ReadFile::run_scanFolder_createReadFileThread_ququeThread(foo, true)
    Setting_getOrderedArrayValue_macro(ScanFolder, size, valueCallback, cache);
}

void ScanCache::expireCache()
{
    cacheFileExist = false;
}
