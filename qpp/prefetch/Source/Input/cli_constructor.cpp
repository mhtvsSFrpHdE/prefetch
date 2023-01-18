#include <QFileInfo>

#include "command_line_argument.h"
#include "..\Core\const_core.h"
#include "..\Setting\const_setting.h"

void CommandLineArgument::CommandLineArgument_parseSettingFileName(int *argIndex, QStringList *argv)
{
    using namespace Const_Core;

    {
        // Assume this argument is the first argument, and not start with "-"
        bool firstArgumentStartWithMinus = (*argv)[Arg::IniArgi].startsWith(Arg::BoolFlagBeginWith);

        // If first argument start with "-", then setting file name is not provided
        if (firstArgumentStartWithMinus)
        {
            // In this case, use default value
            settingFilePath = Const_Setting::DefaultSettingFilePath;
            scanCacheFilePath = Const_Cache::DefaultCacheFilePath;
            return;
        }
    }

    {
        // Setting file name founded, other start from 2nd
        *argIndex = *argIndex + 1;

        // Save
        settingFilePath = (*argv)[Arg::IniArgi];
    }

    {
        // Generate scan cache file name together
        auto settingFile = QFileInfo(settingFilePath);
        scanCacheFilePath = settingFile.baseName() + Const_Cache::DefaultCacheFilePathSuffix;
    }
}

bool CommandLineArgument_parseBoolFlag(QString match, int argIndex, QStringList *argv)
{
    auto arg = (*argv)[argIndex];
    return arg.contains(match);
}

void CommandLineArgument::CommandLineArgument_parseStartup(int argIndex, QStringList *argv)
{
    using namespace Const_Core::Arg;

    bool get = CommandLineArgument_parseBoolFlag(SkipStartup, argIndex, argv);
    if (get)
    {
        skipStartup = true;
    }
}

void CommandLineArgument::CommandLineArgument_parseShowMainWindow(int argIndex, QStringList *argv)
{
    using namespace Const_Core::Arg;

    bool get = CommandLineArgument_parseBoolFlag(ShowMainWindow, argIndex, argv);
    if (get)
    {
        showMainWindow = true;
    }
}

CommandLineArgument::CommandLineArgument(int argc, QStringList argv)
{
    using namespace Const_Core;

    // Create loop index
    // This variable may modify by function before loop
    int argIndex = Arg::ArgBeginIndex;

    // Not found any possible argument
    if (argc < Arg::IniArgc)
    {
        // Put default value
        settingFilePath = Const_Setting::DefaultSettingFilePath;
        scanCacheFilePath = Const_Cache::DefaultCacheFilePath;
        skipStartup = false;
        showMainWindow = false;

        // Terminate
        return;
    }

    CommandLineArgument_parseSettingFileName(&argIndex, &argv);

    // Parse other argument
    for (; argIndex < argc; argIndex++)
    {
        CommandLineArgument_parseStartup(argIndex, &argv);
        CommandLineArgument_parseShowMainWindow(argIndex, &argv);
    }
}
