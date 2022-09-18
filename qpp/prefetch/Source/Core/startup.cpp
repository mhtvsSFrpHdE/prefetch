#include <QProcess>

#include "startup.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"
#include "..\Output\stdout.h"
#include "const_core.h"
#include "start_process.h"
#include "..\Global\global.h"

using namespace Const_Setting::ConfigGroupName;

void (*Startup::startOnce)() = &_startOnce;

void Startup::init(int argc, QStringList argv)
{
    using namespace Const_Core::Arg;

    if (argv.contains(SkipStartup))
    {
        startOnce_remove();
        return;
    }
}

void Startup::startOnce_remove()
{

    startOnce = &Global::dummyFunction;
}

void Startup::_startOnce()
{
    // Disable after fist run
    startOnce_remove();

    // Get startup items
    auto afterPrefetch = Setting::getArrayValue(AfterPrefetch, Setting::setting);
    for (int i = 0; i < afterPrefetch.size(); ++i)
    {
        auto fileName = afterPrefetch[i];
        StartProcess::startProcess(fileName);
    }

    using namespace Const_Core::Message;
    StdOut::printLine(RunStartupItems);
}
