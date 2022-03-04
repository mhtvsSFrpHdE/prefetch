#include <QDir>
#include <QCoreApplication>

#include "setting.h"

QSettings *Setting::setting;

struct TryGetSettingFilePath
{
    bool success = false;
    QString filePath = NULL;
};

TryGetSettingFilePath init_getSettingFilePath(int argc, QStringList argv)
{
    TryGetSettingFilePath tryGetSettingFilePath;

    if (argc != 2)
    {
        return tryGetSettingFilePath;
    }

    tryGetSettingFilePath.filePath = QCoreApplication::arguments()[1];
    tryGetSettingFilePath.success = true;

    return tryGetSettingFilePath;
}

void Setting::init(int argc, QStringList argv)
{
    // Setting file default value
    QString settingFilePath = "prefetch.ini";

    // Get setting file path
    auto getSettingFilePath = init_getSettingFilePath(argc, argv);
    if (getSettingFilePath.success)
    {
        settingFilePath = getSettingFilePath.filePath;
    }
    settingFilePath = QCoreApplication::applicationDirPath() + "/" + settingFilePath;

    // Read ini from exe stored folder
    setting = new QSettings(settingFilePath, QSettings::IniFormat);
}

Setting::GetIntResult Setting::getInt(QString groupName, QString keyName, QSettings *qSettings)
{
    GetIntResult getIntResult;

    qSettings->beginGroup(groupName);

    bool success;
    int result = qSettings->value(keyName).toInt(&success);

    qSettings->endGroup();

    getIntResult.success = success;
    getIntResult.result = success ? result
                                  : 0;

    return getIntResult;
}

QStringList Setting::getArray(QString groupName, QSettings *qSettings)
{
    QStringList values;

    qSettings->beginGroup(groupName);

    auto keysInGroup = qSettings->childKeys();
    for (int i = 0; i < keysInGroup.size(); ++i)
    {

        auto key = keysInGroup[i];
        auto value = qSettings->value(key).toString();

        values << value;
    };

    qSettings->endGroup();

    return values;
}
