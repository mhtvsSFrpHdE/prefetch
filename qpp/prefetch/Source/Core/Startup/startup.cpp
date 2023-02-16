#include <QProcess>

#include "startup.h"
#include "..\..\Output\stdout.h"
#include "..\StartProcess\start_process.h"
#include "..\..\Global\global.h"
#include "..\..\Input\const_input.h"

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

    using namespace Const_Input;
    Global::inputLoopThreadAddress->receiveText_block(Command_Level1::startup);
}
