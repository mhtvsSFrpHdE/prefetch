#include <QSettings>

// Static class
class Setting
{
public:
    static QSettings *setting;

    // Any init code
    static void init();

private:
    // Disallow creating an instance of this object
    Setting() {}
};
