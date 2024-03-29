#include "command_line_argument.h"

QString CommandLineArgument::getSettingFilePath()
{
    return settingFilePath;
}
QString CommandLineArgument::getScanCacheFilePath()
{
    return scanCacheFilePath;
}
bool CommandLineArgument::getSkipStartup()
{
    return skipStartup;
}
bool CommandLineArgument::getScanOnly()
{
    return scanOnly;
}
void CommandLineArgument::setSkipStartup(bool value)
{
    skipStartup = value;
}
bool CommandLineArgument::getShowMainWindow()
{
    return showMainWindow;
}
void CommandLineArgument::setShowMainWindow(bool value)
{
    showMainWindow = value;
}
bool CommandLineArgument::getRocketLaunch()
{
    return rocketLaunch;
}
