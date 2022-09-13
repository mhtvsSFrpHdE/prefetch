#include <QFileInfo>
#include <QApplication>

#include "scan_cache.h"
#include "Thread\read_thread.h"
#include "..\Setting\setting.h"
#include "const_core.h"
#include "ReadFile\read_file.h"

QSettings *ScanCache::cache = NULL;
QString ScanCache::cacheFilePath;
bool ScanCache::cacheFileExist = false;

bool ScanCache::init_cacheFileExist()
{
    auto cacheFile = QFileInfo(cacheFilePath);
    return cacheFile.exists();
}

Setting::GetGenericResult<QString> init_getCacheFilePath(int argc, QStringList argv)
{
    Setting::GetGenericResult<QString> getCacheFilePath;

    if (argc != 2)
    {
        getCacheFilePath.success = false;
        return getCacheFilePath;
    }

    auto settingFile = QFileInfo(argv[1]);
    QString cacheFileName = settingFile.baseName() + Const_Cache::DefaultCacheFilePathSuffix;
    auto cacheFile = QFileInfo(cacheFileName);
    ScanCache::cacheFileExist = cacheFile.exists();

    getCacheFilePath.result = cacheFileName;
    return getCacheFilePath;
}

void ScanCache::init(int argc, QStringList argv)
{
    // Cache file path default value
    cacheFilePath = Const_Cache::DefaultCacheFilePath;

    // Get cache file path
    auto getCacheFilePath = init_getCacheFilePath(argc, argv);
    if (getCacheFilePath.success)
    {
        cacheFilePath = getCacheFilePath.result;
    }
    cacheFilePath = QApplication::applicationDirPath() + Const_Cache::PathSplitter + cacheFilePath;
    cacheFileExist = init_cacheFileExist();

    // Read ini from exe stored folder
    cache = new QSettings(cacheFilePath, QSettings::IniFormat);
}

void ScanCache::saveScanCache(QList<QRunnable *> *readThreadQueueAddress, bool override = false)
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
}

void ScanCache::loadScanCache(QList<QRunnable *> *readThreadQueueAddress)
{
    using namespace Const_Cache::ConfigGroupName;
    using namespace Const_Cache::MetaData_ConfigKeyName;

    auto getSize = Setting::getInt(MetaData, Size, cache);
    auto size = getSize.result;

    Setting_getOrderedArrayValue_macro(ScanFolder, size, ReadFile::run_scanFolder_createReadFileThread_ququeThread, cache);
}

void ScanCache::expireCache()
{
    cacheFileExist = false;
}
