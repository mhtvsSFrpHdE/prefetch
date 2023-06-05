#ifndef Const_Setting_h
#define Const_Setting_h

#include <QString>

// This file should independently to others
// Setting must always available
//
// Use tree structure instead of tiles
//     Tree: type full namespace path is required, but `#define` to shortcut
//     Tiles: type using namespace, then type variable directly without `Namespace::`
//     The reason to decide tree is `#define` way more flexible than `using`
//     If name finally conflict in future
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
        const QString StartupItem = "StartupItem";
        const QString Skip = "Skip";
        const QString SkipProcess = "SkipProcess";
        const QString Thread = "Thread";
        const QString Instance = "Instance";
        const QString CustomTrayMenu = "CustomTrayMenu";
        const QString Instance_MainWindow = "Instance_MainWindow";
    }

    namespace ConfigKeyName
    {
        namespace SkipProcess
        {
            const QString AssumeProcess = "AssumeProcess";
        }

        namespace Thread
        {
            const QString MaxThreadCount = "MaxThreadCount";
            const QString RescanInterval = "RescanInterval";
            const QString PrefetchInterval = "PrefetchInterval";
            const QString ReadThreadPriority = "ReadThreadPriority";
            const QString ReadBufferSize = "ReadBufferSize";
            const QString ProcessStartCooldown = "ProcessStartCooldown";
        }

        namespace Instance
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
            const QString TranslateFolder = "TranslateFolder";
        }

        namespace MainWindow
        {
            const QString Position = "Position";
            const QString Size = "Size";
            const QString Resizable = "Resizable";
        }
    }

    namespace Value
    {
        namespace Thread
        {

            namespace ReadThreadPriority
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
        }

        namespace Instance
        {
            namespace Font
            {
                extern QString Default;
            }

            namespace Language
            {
                extern QString Default;
            }

            namespace TranslateFolder
            {
                extern QString Default;
                const QString DefaultIs = "translate";
            }
        }

        namespace MainWindow
        {
            namespace Position
            {
                extern QString Default;
            }
        }
    }

}
#endif
