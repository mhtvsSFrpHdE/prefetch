#include <QSettings>

// Static class
class Setting
{
public:
    static QSettings *setting;

    // Any init code
    static void init();

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
    static QStringList getArray(const QString &groupName, QSettings *qSettings);

private:
    // Disallow creating an instance of this object
    Setting() {}
};
