#include <QProcess>

#include "startup.h"
#include "..\..\Setting\setting.h"
#include "..\..\Setting\const_setting.h"
#include "..\..\Output\stdout.h"
#include "..\const_core.h"
#include "..\StartProcess\start_process.h"
#include "..\..\Global\global.h"

#define gn Const_Setting::ConfigGroupName

void (*Core_Startup::startOnce)() = &_startOnce;

void Core_Startup::init()
{
    bool skipStartup = Global::commandLineArgumentAddress->getSkipStartup();

    if (skipStartup)
    {
        startOnce_remove();
        return;
    }
}

void Core_Startup::startOnce_remove()
{

    startOnce = &Global::dummyFunction;
}

void Core_Startup::_startOnce()
{
    // Disable after fist run
    startOnce_remove();

    // Get startup items
    auto startupItem = Setting::getArrayValue(gn::StartupItem, Setting::setting);
    for (int i = 0; i < startupItem.size(); ++i)
    {
        auto fileName = startupItem[i];
        Core_StartProcess::startProcess(fileName);
    }

    using namespace Const_Core::Message;
    StdOut::printLine(RunStartupItems);
}
