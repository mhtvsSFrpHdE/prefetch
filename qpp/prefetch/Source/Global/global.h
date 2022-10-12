#ifndef Global_h
#define Global_h

#include <QApplication>

#include "..\Input\Thread\input_loop_thread.h"
#include "..\Core\ReadFile\read_file.h"
#include "..\Interface\TrayIcon\tray_icon.h"
#include "..\Interface\MainWindow\mainwindow.h"

class Global
{
public:
    static QApplication *qGuiApplication;

    static MainWindow *qMainWindow;

    static InputLoopThread *inputLoopThreadAddress;

    static ReadFile *readFileLoopThreadAddress;

    static TrayIcon *trayIconInstanceAddress;

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
