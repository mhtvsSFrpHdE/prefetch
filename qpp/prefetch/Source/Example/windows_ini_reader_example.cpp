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
    auto groupContent = (*settingAddress)[groupName];

    QStringList childKeys;
    for (int i = 0; i < groupContent.size(); ++i)
    {
        childKeys.append(groupContent.at(i).keys());
    }

    return childKeys;
}
