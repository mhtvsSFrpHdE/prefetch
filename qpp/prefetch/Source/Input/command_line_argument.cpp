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
