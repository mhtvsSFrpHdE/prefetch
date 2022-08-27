#include <QSettings>
#include <QString>

// Static class
class Setting
{
public:
    static QSettings *setting;

    // Any init code
    static void init(int argc, QStringList argv);

    template <class T>
    struct GetGenericResult
    {
        T result;
        bool success = true;
    };

    // Give setting group name and key name, return value as bool
    // If fail to parse, result will set to false
    static bool getBool(QString groupName, QString keyName, QSettings *qSettings);

    // Give setting group name and key name, return value as int
    // If fail to parse, result will set to 0
    static GetGenericResult<int> getInt(QString groupName, QString keyName, QSettings *qSettings);

    // Same as getInt, return value as unsigned long
    //     success: The value will first parse to `ULongLong`, success or not depending on parse result
    //     result: `ULongLong` implicit convert to `unsigned long`
    //         If fail to parse, result will set to 0
    static GetGenericResult<unsigned long> getUnsignedLong(QString groupName, QString keyName, QSettings *qSettings);

    // Give setting group name and key name, return value as QString
    // This one return result directly no matter what it is
    //     because QVariant.toString() has no success check
    static QString getString(QString groupName, QString keyName, QSettings *qSettings);

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
    // Give setting group name and key name, return value as raw QVariant
    // So later can convert to other type manually
    // The reason to not use template to convert format:
    //     Qt convert use named function instead of generic type
    //     It's too hard to write correct and maintainable template code right now
    static QVariant getQVariant(QString groupName, QString keyName, QSettings *qSettings);

    // Disallow creating an instance of this object
    Setting() {}
};
