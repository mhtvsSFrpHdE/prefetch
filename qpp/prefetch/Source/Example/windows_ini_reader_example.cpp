#include "windows_ini_example.h"
#include "../Global/const_global.h"

WindowsIniReaderExample::WindowsIniReaderExample(WindowsIniFormatExample *settingAddress)
{
    this->settingAddress = settingAddress;
}

void WindowsIniReaderExample::beginGroup(QString groupName)
{
    this->groupName = groupName;
}
void WindowsIniReaderExample::endGroup()
{
    groupName = Const_Global::CommonString::EmptyString;
}
QStringList WindowsIniReaderExample::childGroups()
{
    return settingAddress->keys();
}
QStringList WindowsIniReaderExample::childKeys()
{
    auto setting = *settingAddress;
    auto groupContent = (*settingAddress)[groupName];

    QStringList childKeys = groupContent.keys();

    return childKeys;
}
QString WindowsIniReaderExample::value(QString key)
{
    QString value = (*settingAddress)[groupName][key];

    return value;
}
