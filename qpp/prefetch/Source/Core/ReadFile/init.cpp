#include "read_file.h"
#include "..\..\Setting\setting.h"
#include "..\Thread\Read\read_thread.h"
#include "..\..\Setting\const_setting.h"
#include "run_sleep.h"

#define gn Const_Setting::ConfigGroupName
#define kn Const_Setting::ConfigKeyName::Thread
void ReadFile::init()
{
    // Get and set thread number
    auto getThreadNumber = Setting::getInt(gn::Thread, kn::MaxThreadCount, Setting::setting);
    if (getThreadNumber.success && getThreadNumber.result >= 1)
    {
        readThreadPool->setMaxThreadCount(getThreadNumber.result);
    }

    // Get prefetch folder
    prefetchFolders = Setting::getArrayValue(gn::PrefetchFolder, Setting::setting);

    // Get exclude folder
    auto excludeFolders = Setting::getArrayValue(gn::ExcludeFolder, Setting::setting);
    for (int i = 0; i < excludeFolders.size(); ++i)
    {
        auto excludeFolderName = QDir(excludeFolders[i]).absolutePath();
        ReadThread::excludeFolders.append(excludeFolderName);
    }

    // Get priority include search patterns
    auto priorityIncludePatterns = Setting::getArrayValue(gn::PriorityIncludePattern, Setting::setting);
    for (int i = 0; i < priorityIncludePatterns.size(); ++i)
    {
        auto priorityIncludePattern = priorityIncludePatterns[i];
        ReadThread::priorityIncludePatterns.append(priorityIncludePattern);
    }

    // Get rescan interval
    auto getRescanInterval = Setting::getInt(gn::Thread, kn::RescanInterval, Setting::setting);
    rescanInterval = getRescanInterval.result;

    // Get prefetch interval
    auto getPrefetchInterval = Setting::getUnsignedLong(gn::Thread, kn::PrefetchInterval, Setting::setting);
    prefetchIntervalInSecond = getPrefetchInterval.result;

    // Set prefetch interval to sleep thread
    sleepThreadAddress = new SleepThread();
    sleepThreadAddress->sleepTimeInSeconds = prefetchIntervalInSecond;

    // Get read thread priority
    auto getReadThreadPriority = Setting::getString(gn::Thread, kn::ReadThreadPriority, Setting::setting);
    readThreadPriority = priorityMap[getReadThreadPriority];

    // Set do not auto delete for thread instance
    ReadThread::autoDeletePreset = false;
}
