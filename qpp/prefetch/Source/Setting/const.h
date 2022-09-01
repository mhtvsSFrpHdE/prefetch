#include <QString>

namespace Const_Setting
{
    const QString DefaultSettingFilePath = "prefetch.ini";
    const QString PathSplitter = "/";

    namespace ConfigGroupName
    {
        const QString PrefetchFolder = "PrefetchFolder";
        const QString ExcludeFolder = "ExcludeFolder";
        const QString PriorityIncludePattern = "PriorityIncludePattern";
        const QString AfterPrefetch = "AfterPrefetch";
        const QString Thread = "Thread";
        const QString Instance = "Instance";

    }
    namespace Thread_ConfigKeyName
    {
        const QString MaxThreadCount = "MaxThreadCount";
        const QString RescanInterval = "RescanInterval";
        const QString PrefetchInterval = "PrefetchInterval";
        const QString ReadThreadPriority = "ReadThreadPriority";

    }

    namespace ReadThreadPriority_Value
    {
        const QString IdlePriority = "IdlePriority";
        const QString LowestPriority = "LowestPriority";
        const QString LowPriority = "LowPriority";
        const QString NormalPriority = "NormalPriority";
        const QString HighPriority = "HighPriority";
        const QString HighestPriority = "HighestPriority";
        const QString TimeCriticalPriority = "TimeCriticalPriority";
        const QString InheritPriority = "InheritPriority";
    }

    namespace Instance_ConfigKeyName
    {
        const QString Name = "Name";
        const QString StartToTray = "StartToTray";
        const QString MinimizeToTray = "MinimizeToTray";
        const QString MaximumBlockCount = "MaximumBlockCount";
        const QString Font = "Font";
        const QString FontSize = "FontSize";
        const QString PrintOffset = "PrintOffset";
        const QString ZoomLevel = "ZoomLevel";
    }

    namespace Font_Value
    {
        const QString Default = "<default>";
    }
}