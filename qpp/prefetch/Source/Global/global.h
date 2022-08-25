#include <QApplication>

#include "..\Input\Thread\loop_thread.h"
#include "..\Core\read_file.h"
#include "..\Interface\TrayIcon\tray_icon.h"
#include "..\Interface\MainWindow\mainwindow.h"

// Static class
class Global
{
public:
    static QApplication *qGuiApplication;

    static MainWindow *qMainWindow;

    static LoopThread *inputLoopThreadAddress;

    static ReadFile *readFileLoopThreadAddress;

    static TrayIcon *trayIconInstanceAddress;

    // Any init code
    static void init(int argc, char *argv[]);

    QString getSettingFilePath();

private:
    // Disallow creating an instance of this object
    Global() {}
};
