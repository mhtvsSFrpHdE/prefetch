#include "skip.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"
#include "start_process.h"

QString Skip::assumeProcess;
QStringList Skip::skipProcessList;

#define gn Const_Setting::ConfigGroupName
#define skn Const_Setting::ConfigKeyName::SkipProcess
void Skip::init()
{
    assumeProcess = Setting::getString(gn::Skip, skn::AssumeProcess, Setting::setting);
    skipProcessList.append(Setting::getArrayValue(gn::SkipProcess, Setting::setting));
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
