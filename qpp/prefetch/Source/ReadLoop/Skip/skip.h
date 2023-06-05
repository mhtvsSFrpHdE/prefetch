#include <QString>
#include <QStringList>

class ReadLoop_Skip
{
public:
    // Any init code
    static void init();

    static bool check();

private:
    static QString assumeProcess;
    static QStringList skipProcessList;
};
