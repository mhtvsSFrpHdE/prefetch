#ifndef SettingInterface_h
#define SettingInterface_h

#include <QString>
#include <QMap>

// This interface ensure all setting class support same set of features
class SettingInterface
{
public:
    // Give setting group name and key name, confirm exist in config
    virtual bool getExist(QString groupName, QString keyName, void *settingAddress) = 0;
};

#endif
