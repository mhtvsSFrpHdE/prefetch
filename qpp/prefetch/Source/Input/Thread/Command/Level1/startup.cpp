#include "parent_define.h"
#include "../../../../Setting/setting.h"
#include "../../../../Setting/const_setting.h"
#include "../../../../ReadLoop/StartProcess/start_process.h"
#include "../../../../Output/stdout.h"
#include "../../../../ReadLoop/const_read_loop.h"
#include "../../../../Global/global.h"

#define gn Const_Setting::ConfigGroupName
#define tkn Const_Setting::ConfigKeyName::Thread

void Parent_Prefetch::startup()
{
    StdOut::printLine(Const_ReadLoop::Message::RunStartupItems);

    // Get startup items
    auto startupItem = Setting::getArrayValue(gn::StartupItem, Setting::setting);
    for (int i = 0; i < startupItem.size(); ++i)
    {
        auto fileName = startupItem[i];
        ReadLoop_StartProcess::startProcess(fileName);
    }

    // Hack rocket launch
    // If run startup item without manually sleep
    //     When rocket launch and code run too fast
    //     desired process may not run
    //     (QProcess::waitForStarted not work)
    // Even msleep(0) will do the trick, strange
    bool rocketLaunch = Global::commandLineArgumentAddress->getRocketLaunch();
    if (rocketLaunch)
    {
        auto getStartupItemCooldownMilliseconds = Setting::getUnsignedLong(gn::Thread, tkn::StartupItemCooldown, Setting::setting);
        msleep(getStartupItemCooldownMilliseconds.result);
    }
}
