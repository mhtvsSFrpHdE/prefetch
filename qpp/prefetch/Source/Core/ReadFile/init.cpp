#include "read_file.h"
#include "..\..\Setting\setting.h"
#include "..\Thread\read_thread.h"
#include "..\..\Setting\const_setting.h"
#include "..\const_core.h"

void ReadFile::init()
{
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Thread_ConfigKeyName;
    using namespace Const_Core::Message;

    // Get and set thread number
    auto getThreadNumber = Setting::getInt(Thread, MaxThreadCount, Setting::setting);
    if (getThreadNumber.success && getThreadNumber.result >= 1)
    {
        readThreadPool->setMaxThreadCount(getThreadNumber.result);
    }

    // Get prefetch folder
    prefetchFolders = Setting::getArrayValue(PrefetchFolder, Setting::setting);

    // Get exclude folder
    auto excludeFolders = Setting::getArrayValue(ExcludeFolder, Setting::setting);
    for (int i = 0; i < excludeFolders.size(); ++i)
    {
        auto excludeFolderName = QDir(excludeFolders[i]).absolutePath();
        ReadThread::excludeFolders.append(excludeFolderName);
    }

    // Get priority include search patterns
    auto priorityIncludePatterns = Setting::getArrayValue(PriorityIncludePattern, Setting::setting);
    for (int i = 0; i < priorityIncludePatterns.size(); ++i)
    {
        auto priorityIncludePattern = priorityIncludePatterns[i];
        ReadThread::priorityIncludePatterns.append(priorityIncludePattern);
    }

    // Get rescan interval
    auto getRescanInterval = Setting::getInt(Thread, RescanInterval, Setting::setting);
    rescanInterval = getRescanInterval.result;

    // Get prefetch interval
    auto getPrefetchInterval = Setting::getUnsignedLong(Thread, PrefetchInterval, Setting::setting);
    prefetchIntervalInSecond = getPrefetchInterval.result;

    // Get read thread priority
    auto getReadThreadPriority = Setting::getString(Thread, ReadThreadPriority, Setting::setting);
    readThreadPriority = priorityMap[getReadThreadPriority];

    // Set do not auto delete for thread instance
    ReadThread::autoDeletePreset = false;
}
