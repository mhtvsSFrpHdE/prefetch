#ifndef Const_Setting_h
#define Const_Setting_h

#include <QString>

// This file should independently to others
// Setting must always available
namespace Const_Setting
{
    const QString DefaultSettingFilePath = "prefetch.ini";
    extern QString PathSplitter;
    extern QString StringListSplitter;

    namespace ConfigGroupName
    {
        const QString PrefetchFolder = "PrefetchFolder";
        const QString ExcludeFolder = "ExcludeFolder";
        const QString PriorityIncludePattern = "PriorityIncludePattern";
        const QString AfterPrefetch = "AfterPrefetch";
        const QString Thread = "Thread";
        const QString Instance = "Instance";
        const QString CustomTrayMenu = "CustomTrayMenu";
        const QString cgn_MainWindow = "MainWindow";

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
        const QString TrayMenuMinimalWidth = "TrayMenuMinimalWidth";
        const QString Language = "Language";
    }

    namespace Instance_Font_Value
    {
        extern QString Default;
    }

    namespace Instance_Language_Value
    {
        extern QString Default;
    }

    namespace MainWindow_ConfigKeyName
    {
        const QString Position = "Position";
        const QString Size = "Size";
        const QString Resizable = "Resizable";
    }

    namespace MainWindow_Position_Value
    {
        extern QString Default;
    }
}
#endif
