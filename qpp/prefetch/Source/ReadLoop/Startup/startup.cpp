#include <QProcess>

#include "startup.h"
#include "../../Output/stdout.h"
#include "../StartProcess/start_process.h"
#include "../../Global/global.h"
#include "../../ReadLoop/const_read_loop.h"
#include "../../Setting/setting.h"
#include "../../Setting/const_setting.h"

#define gn Const_Setting::ConfigGroupName
#define tkn Const_Setting::ConfigKeyName::Thread

void (*ReadLoop_Startup::startOnce)() = &_startOnce;

void ReadLoop_Startup::init()
{
    bool skipStartup = Global::commandLineArgumentAddress->getSkipStartup();

    if (skipStartup)
    {
        startOnce_remove();
        return;
    }
}

void ReadLoop_Startup::startOnce_remove()
{

    startOnce = &Global::dummyFunction;
}

void ReadLoop_Startup::_startOnce()
{
    // Disable after fist run
    startOnce_remove();

    StdOut::printLine(Const_ReadLoop::Message::RunStartupItems);

    // Get startup items
    auto startupItem = Global::windowsIniExampleAddress->getArrayValue(gn::StartupItem, &Global::windowsIniExampleAddress->setting);
    for (int i = 0; i < startupItem.size(); ++i)
    {
        auto fileName = startupItem[i];
        ReadLoop_StartProcess::startProcess(fileName);
    }

    bool rocketLaunch = Global::commandLineArgumentAddress->getRocketLaunch();
    if (rocketLaunch)
    {
        auto getProcessStartCooldownMilliseconds = Setting::getUnsignedLong(gn::Thread, tkn::ProcessStartCooldown, Setting::setting);
        // msleep: See Document\KnownIssue\QtComponent\ProcessStart\README.md for more details
        msleep(getProcessStartCooldownMilliseconds.result);
    }
}
