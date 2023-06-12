#include "read_loop.h"
#include "../Setting/setting.h"
#include "../Setting/const_setting.h"
#include "ReadFile/read_file_thread.h"
#include "Sleep/sleep.h"
#include "../GLobal/global.h"

#define gn Const_Setting::ConfigGroupName
#define kn Const_Setting::ConfigKeyName::Thread

void ReadLoop::init()
{
    // Get and set thread number
    auto getThreadNumber = Setting::getInt(gn::Thread, kn::MaxThreadCount, Setting::setting);
    if (getThreadNumber.success && getThreadNumber.result >= 1)
    {
        readThreadPool->setMaxThreadCount(getThreadNumber.result);
    }

    // Get prefetch folder
    prefetchFolders.append(Global::windowsIniExampleAddress->getArrayValue(gn::PrefetchFolder, &Global::windowsIniExampleAddress->setting));

    // Get exclude folder
    auto excludeFolders = Global::windowsIniExampleAddress->getArrayValue(gn::ExcludeFolder, &Global::windowsIniExampleAddress->setting);
    for (int i = 0; i < excludeFolders.size(); ++i)
    {
        auto excludeFolderName = QDir(excludeFolders[i]).absolutePath();
        ReadLoop_ReadFileThread::excludeFolders.append(excludeFolderName);
    }

    // Get priority include search patterns
    auto priorityIncludePatterns = Global::qSettingAddress->getArrayValue(gn::PriorityIncludePattern, Setting::setting);
    for (int i = 0; i < priorityIncludePatterns.size(); ++i)
    {
        auto priorityIncludePattern = priorityIncludePatterns[i];
        ReadLoop_ReadFileThread::priorityIncludePatterns.append(priorityIncludePattern);
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
    ReadLoop_ReadFileThread::autoDeletePreset = false;
}
