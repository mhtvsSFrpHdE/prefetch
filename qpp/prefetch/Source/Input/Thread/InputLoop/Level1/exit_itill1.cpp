#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Global\global.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::exit_quiet()
{
    // Remove MainWindow
    Global::qMainWindow->hide();

    // Remove tray icon
    TrayIcon::stop();

    // Stop QT event loop on main thread
    Global::qGuiApplication->quit();
}

void Parent::exit()
{
    using namespace Const_Input::Message;
    StdOut::printLine(TryingToExit1);
    StdOut::printLine(TryingToExit2);

    exit_quiet();
}
