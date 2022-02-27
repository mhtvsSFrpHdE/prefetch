#include <QSettings>

// Static class
class Setting
{
public:
    // Global QSettings object, it's a pointer
    static QSettings *setting;

    // Any init code
    static void init();

private:
    // Disallow creating an instance of this object
    Setting() {}
};
