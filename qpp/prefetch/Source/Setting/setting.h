#include <QSettings>
#include <QString>

class Setting
{
public:
    static QSettings *setting;
    static QString settingFilePath;

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

    // Give setting group name and key name, return value as QString
    //     If value may contains comma, use this sightly slower overload, but space between will trimmed
    //     Or a regular getString with comma value will fail to parse
    //     Quote the string in ini file should be better solution
    //
    // https://stackoverflow.com/questions/18052930/how-to-read-a-value-using-qsetting-if-the-value-contains-comma-character
    // https://stackoverflow.com/questions/27557727/qsettingsiniformat-values-with-returned-as-qstringlist
    static QString getCommaString(QString groupName, QString keyName, QSettings *qSettings);

    // Give setting group name and key name, return value as QStringList
    //     If a value contains comma (","), QSettings will not convert it to string
    static QStringList getStringList(QString groupName, QString keyName, QSettings *qSettings);

    // Save setting value, QString should be fine for most type
    static void setValue(QString groupName, QString keyName, QString value, QSettings *qSettings);

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
    static QStringList getArrayValue(QString groupName, QSettings *qSettings);

    // Act like getArrayValue, but sorting by array index
    static QStringList getOrderedArrayValue(QString groupName, int size, QSettings *qSettings);

// Act like getOrderedArrayValue
//     Pick up this one to iterate only once
#define Setting_getOrderedArrayValue_macro(groupName, sizeExpression, valueCallback, qSettings) \
    {                                                                                           \
        qSettings->beginGroup(groupName);                                                       \
                                                                                                \
        for (int i = 0; i < sizeExpression; ++i)                                                \
        {                                                                                       \
            auto key = QString::number(i);                                                      \
            auto value = qSettings->value(key).toString();                                      \
                                                                                                \
            valueCallback(value);                                                               \
        };                                                                                      \
                                                                                                \
        qSettings->endGroup();                                                                  \
    }

    // Act like getArrayValue, but also return keys
    static QMap<QString, QString> getArray(QString groupName, QSettings *qSettings);

    // Reverse of getArray
    //     Custom key name, but sorting rule are made by Qt
    static void setArray(QString groupName, QMap<QString, QString> array, QSettings *qSettings);
    // Reverse of getArray
    //     Key name is array index, and sorting by array index
    //     Pick up this one to "assume" HDD will faster when working on same directory
    static void setArray(QString groupName, QStringList array, QSettings *qSettings);
// Reverse of getArray
//     Pick up this one to iterate only once
#define Setting_setArray_macro(groupName, array, arraySizeExpression, itemType, getValueExpression, qSettings) \
    {                                                                                                          \
        qSettings->beginGroup(groupName);                                                                      \
                                                                                                               \
        for (int i = 0; i < arraySizeExpression; ++i)                                                          \
        {                                                                                                      \
            auto item = (itemType)array[i];                                                                    \
            auto key = QString::number(i);                                                                     \
            auto value = getValueExpression;                                                                   \
                                                                                                               \
            qSettings->setValue(key, value);                                                                   \
        }                                                                                                      \
                                                                                                               \
        qSettings->endGroup();                                                                                 \
    }

private:
    // Give setting group name and key name, return value as raw QVariant
    // So later can convert to other type manually
    // The reason to not use template to convert format:
    //     Qt convert use named function instead of generic type
    //     It's too hard to write correct and maintainable template code right now
    static QVariant getQVariant(QString groupName, QString keyName, QSettings *qSettings);
};
