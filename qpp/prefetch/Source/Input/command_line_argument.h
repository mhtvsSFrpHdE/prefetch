#ifndef Command_Line_Argument_h
#define Command_Line_Argument_h

#include <QStringList>
#include <QString>

class CommandLineArgument
{
public:
    CommandLineArgument(int argc, QStringList argv);

    QString getSettingFilePath();
    QString getScanCacheFilePath();
    bool getSkipStartup();
    // Only use if reasonable, because command line argument is generally read only
    void setSkipStartup(bool value);
    bool getShowMainWindow();
    // Only use if reasonable, because command line argument is generally read only
    void setShowMainWindow(bool value);
    bool getRocketLaunch();

    // Generate restart command
    QString toString();

private:
    // Read only internal variable
    QString settingFilePath;
    QString scanCacheFilePath;
    bool skipStartup;
    bool showMainWindow;
    bool rocketLaunch;

    // Parse first argument (setting file name, but also use as instance name like scan cache)
    void CommandLineArgument_parseSettingFileName(int *argIndex, QStringList *argv);

    // Parse skip startup
    void CommandLineArgument_parseStartup(int argIndex, QStringList *argv);

    // Parse show main window
    void CommandLineArgument_parseShowMainWindow(int argIndex, QStringList *argv);

    // Parse rocket launch
    void CommandLineArgument_parseRocketLaunch(int argIndex, QStringList *argv);

    // Disallow create without argument
    CommandLineArgument() {}
};

#endif
