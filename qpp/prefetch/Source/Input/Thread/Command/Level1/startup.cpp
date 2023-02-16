#include "parent_define.h"
#include "..\..\..\..\Setting\setting.h"
#include "..\..\..\..\Setting\const_setting.h"
#include "..\..\..\..\Core\StartProcess\start_process.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\const_core.h"

#define gn Const_Setting::ConfigGroupName

void Parent_Prefetch::startup()
{
    // Get startup items
    auto startupItem = Setting::getArrayValue(gn::StartupItem, Setting::setting);
    for (int i = 0; i < startupItem.size(); ++i)
    {
        auto fileName = startupItem[i];
        Core_StartProcess::startProcess(fileName);
    }

    StdOut::printLine(Const_Core::Message::RunStartupItems);
}
