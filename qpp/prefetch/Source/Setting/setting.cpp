#include <QDir>
#include <QApplication>

#include "setting.h"
#include "const_setting.h"

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

    tryGetSettingFilePath.filePath = argv[1];
    tryGetSettingFilePath.success = true;

    return tryGetSettingFilePath;
}

void Setting::init(int argc, QStringList argv)
{
    using namespace Const_Setting;

    // Setting file path default value
    QString settingFilePath = DefaultSettingFilePath;

    // Get setting file path
    auto getSettingFilePath = init_getSettingFilePath(argc, argv);
    if (getSettingFilePath.success)
    {
        settingFilePath = getSettingFilePath.filePath;
    }
    settingFilePath = QApplication::applicationDirPath() + PathSplitter + settingFilePath;

    // Read ini from exe stored folder
    setting = new QSettings(settingFilePath, QSettings::IniFormat);
}

Setting::GetGenericResult<int> Setting::getInt(QString groupName, QString keyName, QSettings *qSettings)
{
    // Result template
    GetGenericResult<int> getIntResult;

    auto qvariant = getQVariant(groupName, keyName, qSettings);

    // Parse
    bool success;
    int result = qvariant.toInt(&success);

    // Fill result template
    getIntResult.success = success;
    getIntResult.result = success ? result
                                  : 0;

    return getIntResult;
}

Setting::GetGenericResult<unsigned long> Setting::getUnsignedLong(QString groupName, QString keyName, QSettings *qSettings)
{
    // Result template
    GetGenericResult<unsigned long> getUnsignedlongResult;

    auto qvariant = getQVariant(groupName, keyName, qSettings);

    // Parse
    bool success;
    // Warning: implicit conversion from `unsigned long long` to `unsigned long`
    auto result = qvariant.toULongLong(&success);

    // Fill result template
    getUnsignedlongResult.success = success;
    getUnsignedlongResult.result = success ? result
                                           : 0;

    return getUnsignedlongResult;
}

bool Setting::getBool(QString groupName, QString keyName, QSettings *qSettings)
{
    auto qvariant = getQVariant(groupName, keyName, qSettings);

    auto result = qvariant.toBool();

    return result;
}

QString Setting::getString(QString groupName, QString keyName, QSettings *qSettings)
{
    auto qvariant = getQVariant(groupName, keyName, qSettings);

    auto result = qvariant.toString();

    return result;
}

QStringList Setting::getArrayValue(QString groupName, QSettings *qSettings)
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

QMap<QString, QString> Setting::getArray(QString groupName, QSettings *qSettings)
{
    QMap<QString, QString> result;

    qSettings->beginGroup(groupName);

    auto keysInGroup = qSettings->childKeys();
    for (int i = 0; i < keysInGroup.size(); ++i)
    {

        auto key = keysInGroup[i];
        auto value = qSettings->value(key).toString();
        result.insert(key, value);
    };

    qSettings->endGroup();

    return result;
}

void Setting::setArray(QString groupName, QMap<QString, QString> array, QSettings *qSettings)
{

    qSettings->beginGroup(groupName);

    QMap<QString, QString>::const_iterator mapIterator;
    for (mapIterator = array.constBegin(); mapIterator != array.constEnd(); ++mapIterator)
    {
        qSettings->setValue(mapIterator.key(), mapIterator.value());
    }

    qSettings->endGroup();

    return;
}

QVariant Setting::getQVariant(QString groupName, QString keyName, QSettings *qSettings)
{
    qSettings->beginGroup(groupName);

    QVariant result = qSettings->value(keyName);

    qSettings->endGroup();

    return result;
}