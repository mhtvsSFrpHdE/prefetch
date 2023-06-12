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

    // Give a setting group name, return all values under that group
    // Use case: retrieve user input array
    //
    // Example:
    //     setting.ini
    //         [Array]
    //         value1=1
    //         value2=2
    //         value3=3
    //     auto myArrayValue = getArrayValue("Array");
    //         myArrayValue content: {1,2,3}
    virtual QStringList getArrayValue(QString groupName, void *settingAddress) = 0;
};

#endif
