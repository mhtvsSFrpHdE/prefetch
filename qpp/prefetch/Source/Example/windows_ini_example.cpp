#include <QFile>

#include "windows_ini_example.h"
#include "../Global/global.h"
#include "../Setting/const_setting.h"
#include "../Output/log.h"
#include "../Example/exception_example.h"

void WindowsIniExample::init()
{
    using namespace Const_Setting;

    // Get setting file path
    settingFilePath = Global::commandLineArgumentAddress->getSettingFilePath();

    // Fill with applicationDirPath
    settingFilePath = QApplication::applicationDirPath() + PathSplitter + settingFilePath;

    // Read ini from exe stored folder
    QFile file(settingFilePath);
    LAST_KNOWN_POSITION(2)
    readWindowsIniFile(file, setting);

    // Config version check is done by QSettings
}

void WindowsIniExample::readWindowsIniFile(QFile &file, WindowsIniFormatExample &qsetting)
{
    using namespace Const_Setting::WindowsIniFormat;

    // What if file not available
    bool opened = file.open(QIODevice::ReadOnly);
    if (opened == false)
    {
        QString exception = Const_Setting::Exception::FailedToOpenFile;
        QString exceptionUiText = exception + Const_Setting::Exception::FailedToOpenFile_UI + settingFilePath;
        LAST_KNOWN_POSITION(2)
        ExceptionExample::throwException(exception, exceptionUiText);
    }

    QString groupName = DefaultGroupName;
    QMap<QString, QString> groupContent;

    // Read through QIODevice (QFile)
    while (file.atEnd() == false)
    {
        // Read as ByteArray
        auto rawLineContent = file.readLine();
        // To UTF8, trimmed
        QString lineContent = QString::fromUtf8(rawLineContent).trimmed();
        // Ignore empty line
        if (lineContent.size() == 0)
        {
            continue;
        }

        // Check start with [
        auto firstCharacter = lineContent.at(0);
        // Yes, update group name
        if (firstCharacter == BeginGroup)
        {
            // Commit previous result
            qsetting.insert(groupName, groupContent);
            groupContent.clear();

            // Update group name
            groupName = lineContent.mid(1, lineContent.size() - 2);
        }
        // No, try parse this line
        else
        {
            // Get first index of '='
            auto splitterIndex = lineContent.indexOf(KeyValueSplitter);
            auto keyName = lineContent.left(splitterIndex);
            // No preserve '=' in value string
            auto value = lineContent.mid(splitterIndex + 1);

            groupContent.insert(keyName, value);
        }
    }

    // Commit last result
    qsetting.insert(groupName, groupContent);
    qsetting.remove(DefaultGroupName);
    file.close();
}

bool WindowsIniExample::getExist(QString groupName, QString keyName, void *settingAddress)
{
    WindowsIniFormatExample *typedSettingAddress = (WindowsIniFormatExample *)settingAddress;
    WindowsIniReaderExample setting(typedSettingAddress);

    // All child group from root node
    auto rootChildGroups = setting.childGroups();

    bool groupNameNotExist = rootChildGroups.contains(groupName) == false;
    if (groupNameNotExist)
    {
        return false;
    }

    // All child key from group name
    setting.beginGroup(groupName);
    auto groupChildKeys = setting.childKeys();
    setting.endGroup();

    bool keyNameNotExist = groupChildKeys.contains(keyName) == false;
    if (keyNameNotExist)
    {
        return false;
    }

    return true;
}
