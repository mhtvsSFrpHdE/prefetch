#include <QProcess>

#include "startup.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"
#include "..\Output\stdout.h"
#include "const_core.h"
#include "start_process.h"

using namespace Const_Setting::ConfigGroupName;

bool Startup::started = false;

void Startup::startOnce()
{
    // Disable after fist run
    if (started)
    {
        return;
    }
    started = true;

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
