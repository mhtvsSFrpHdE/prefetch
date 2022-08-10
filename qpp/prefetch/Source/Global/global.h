#include <QApplication>

#include "..\Input\Thread\loop_thread.h"
#include "..\Core\read_file.h"

// Static class
class Global
{
public:
    static QApplication *qGuiApplication;

    static LoopThread *inputLoopThreadAddress;

    static ReadFile *readFileLoopThreadAddress;

    // Any init code
    static void init(int argc, char *argv[]);

    QString getSettingFilePath();

private:
    // Disallow creating an instance of this object
    Global() {}
};
