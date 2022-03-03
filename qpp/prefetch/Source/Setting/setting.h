#include <QSettings>
#include <QString>

// Static class
class Setting
{
public:
    static QSettings *setting;

    // Any init code
    static void init();

    struct GetIntResult
    {
        int result = 0;
        bool success = true;
    };
    // Give setting group name and key name, return value as int
    // If fail to parse int, result will set to 0
    static GetIntResult getInt(QString groupName, QString keyName, QSettings *qSettings);

    // Give a setting group name, return all values under that group
    // Use case: retrieve user input array
    //
    // Example:
    //     setting.ini
    //         [Array]
    //         value1=1
    //         value2=2
    //         value3=3
    //     auto myArray = getArray("Array");
    //         myArray content: {1,2,3}
    static QStringList getArray(QString groupName, QSettings *qSettings);

private:
    // Disallow creating an instance of this object
    Setting() {}
};
