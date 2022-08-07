#include <QCoreApplication>

#include "..\Input\Thread\loop_thread.h"

// Static class
class Global
{
public:
    static QCoreApplication *qCoreApplication;

    static LoopThread *inputLoopThreadAddress;

    // Any init code
    static void init(int argc, char *argv[]);

    QString getSettingFilePath();

private:
    // Disallow creating an instance of this object
    Global() {}
};
