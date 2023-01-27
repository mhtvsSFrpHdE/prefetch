#include "parent_define.h"
#include "..\..\..\..\Global\global.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"

void Parent_Prefetch::exit_quiet()
{
    // Remove MainWindow
    Global::qMainWindow->hide();

    // Remove tray icon
    TrayIcon::stop();

    // Stop QT event loop on main thread
    Global::qGuiApplication->quit();
}

void Parent_Prefetch::exit()
{
    using namespace Const_Input::Message;
    StdOut::printLine(TryingToExit1);
    StdOut::printLine(TryingToExit2);

    Global::runOnUiThreadAddress->run_block(&exit_quiet);
}
