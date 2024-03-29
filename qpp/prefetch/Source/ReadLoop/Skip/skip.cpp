#include "skip.h"
#include "../../Setting/setting.h"
#include "../../Setting/const_setting.h"
#include "../StartProcess/start_process.h"
#include "../../Global/global.h"

QString ReadLoop_Skip::assumeProcess;
QStringList ReadLoop_Skip::skipProcessList;

#define gn Const_Setting::ConfigGroupName
#define skn Const_Setting::ConfigKeyName::SkipProcess

void ReadLoop_Skip::init()
{
    assumeProcess = Setting::getString(gn::Skip, skn::AssumeProcess, Setting::setting);
    skipProcessList.append(Global::qSettingAddress->getArrayValue(gn::SkipProcess, Setting::setting));
}

bool ReadLoop_Skip::check()
{
    // If skipProcessList is empty
    // Default to true
    bool processNotRunning = true;

    // Ignore check when rocket launch specified
    bool rocketLaunch = Global::commandLineArgumentAddress->getRocketLaunch();
    if (rocketLaunch)
    {
        return processNotRunning;
    }

    for (int i = 0; i < skipProcessList.size(); ++i)
    {
        auto skipProcessName = skipProcessList[i];
        auto processOutput = ReadLoop_StartProcess::startProcessGetStdOut(skipProcessName);

        processNotRunning = processOutput.startsWith(assumeProcess);
        if (processNotRunning == false)
        {
            // Busted! return false
            break;
        }
    }

    return processNotRunning;
}
