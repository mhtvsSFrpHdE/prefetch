#ifndef WindowsIniExample_h
#define WindowsIniExample_h

#include <QFile>
#include <QSettings>
#include <QStringList>

#include "../Setting/setting_interface.h"

typedef QHash<QString, QMap<QString, QString>> WindowsIniFormatExample;

// QSettings always come with file on disk or registry on Windows platform (persistence storage)
// To prevent that, use type WindowsIniFormatExample
class WindowsIniExample : public SettingInterface
{
public:
    void init();
    void readWindowsIniFile(QFile &file, WindowsIniFormatExample &setting);
    bool getExist(QString groupName, QString keyName, void *settingAddress) override;
    QStringList getArrayValue(QString groupName, void *settingAddress) override;

    WindowsIniFormatExample setting;
    QString settingFilePath;
};

// A wrapper to read Windows ini in similar way to QSettings
class WindowsIniReaderExample
{
public:
    WindowsIniReaderExample(WindowsIniFormatExample *setting);
    void beginGroup(QString groupName);
    void endGroup();
    QStringList childGroups();
    QStringList childKeys();
    QString value(QString key);

    WindowsIniFormatExample *settingAddress;
    QString groupName;
};

#endif
