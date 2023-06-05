#include "command_line_argument.h"
#include "../ReadLoop/const_read_loop.h"
#include "../Global/const_global.h"
#include "const_input.h"
#include "../Setting/const_setting.h"
#include "../Global/global.h"

void toString_appendBoolFlag(QString flag, QString *command)
{
    using namespace Const_Global::CommonString;
    using namespace Const_ReadLoop;

    *command = *command + Space + Arg::BoolFlagBeginWith + flag;
}
QString CommandLineArgument::toString()
{
    using namespace Const_Input;
    using namespace Const_Global::CommonString;
    using namespace Const_ReadLoop;

    // Get self exe full path
    auto argv = Global::qGuiApplication->arguments();
    auto selfExePath = QFileInfo(argv[0]).absoluteFilePath();

    // Self command template
    // `run "prefetch.exe"`
    auto self_command = Command_Level2::run_withSplitter + Quote + selfExePath + Quote;

    // Setting file
    // `... chromium.ini`
    if (settingFilePath != Const_Setting::DefaultSettingFilePath)
    {
        self_command = self_command + Space + settingFilePath;
    }

    // Bool flags
    if (skipStartup)
    {
        toString_appendBoolFlag(Arg::SkipStartup, &self_command);
    }
    if (showMainWindow)
    {
        toString_appendBoolFlag(Arg::ShowMainWindow, &self_command);
    }

    return self_command;
}
