#include <QDir>
#include <QCoreApplication>

#include "setting.h"

QSettings *Setting::setting;

void Setting::init()
{
    // Read ini from exe stored folder
    setting = new QSettings(QCoreApplication::applicationDirPath() + "/prefetch.ini", QSettings::IniFormat);
}

Setting::GetIntResult Setting::getInt(QString groupName, QString keyName, QSettings *qSettings)
{
    GetIntResult getIntResult;

    qSettings->beginGroup(groupName);

    bool success;
    int result = qSettings->value(keyName).toInt(&success);

    qSettings->endGroup();

    getIntResult.success = success;
    getIntResult.result = result;

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
