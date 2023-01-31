#include "skip.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"
#include "start_process.h"

QString Skip::assumeProcess;
QStringList Skip::skipProcessList;

void Skip::init()
{
    using namespace Const_Setting;
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::ConfigKeyName::SkipProcess;

    assumeProcess = Setting::getString(ConfigGroupName::Skip, AssumeProcess, Setting::setting);
    // TODO: better to use pointer to avoid deep copy?
    skipProcessList = Setting::getArrayValue(SkipProcess, Setting::setting);
}

bool Skip::check()
{
    // Default to true if skipProcessList is empty
    bool processNotRunning = true;

    for (int i = 0; i < skipProcessList.size(); ++i)
    {
        auto skipProcessName = skipProcessList[i];
        auto processOutput = StartProcess::startProcessGetStdOut(skipProcessName);

        processNotRunning = processOutput.startsWith(assumeProcess);
        if (processNotRunning == false)
        {
            // Busted! return false
            break;
        }
    }

    return processNotRunning;
}
