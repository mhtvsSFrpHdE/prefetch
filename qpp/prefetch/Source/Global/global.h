#ifndef Global_h
#define Global_h

#include <QApplication>

#include "../Example/run_on_ui_thread_example.h"
#include "../Input/Thread/input_loop_thread.h"
#include "../ReadLoop/read_loop.h"
#include "../Interface/TrayIcon/tray_icon.h"
#include "../Interface/MainWindow/mainwindow.h"
#include "../Input/command_line_argument.h"
#include "../Setting/setting_interface.h"

class Global
{
public:
    static QApplication *qGuiApplication;

    static RunOnUiThreadExample *runOnUiThreadAddress;

    static MainWindow *qMainWindow;

    static InputLoopThread *inputLoopThreadAddress;

    static ReadLoop *readLoopThreadAddress;

    static TrayIcon *trayIconInstanceAddress;

    static CommandLineArgument *commandLineArgumentAddress;

    static SettingInterface *qSettingInterfaceAddress;

    // Any init code
    static void init(int argc, char *argv[]);

    QString getSettingFilePath();

    // A function address that does nothing
    static void dummyFunction(){};
    template <class T = int>
    static void dummyFunctionT(T){};
    // static void dummyFunctionT(T, T){};
    // and more...
};

#endif
