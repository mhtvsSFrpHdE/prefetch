#include "stdin.h"

#include "..\Global\global.h"
#include "..\Output\log.h"
#include "..\Example\semaphore_example.h"

QSemaphore *StdIn::freezeSemaphore = NULL;

void StdIn::freeze()
{
    // MainWindow
    Global::qMainWindow->sendCommand_freeze();

    // Tray menu
    Global::trayIconInstanceAddress->freeze();
}

void StdIn::restore()
{
    // MainWindow
    Global::qMainWindow->sendCommand_restore();

    // Tray menu
    Global::trayIconInstanceAddress->restore();

    // Release mutex
    LAST_KNOWN_POSITION(4)
    SemaphoreExample::unlock(StdIn::freezeSemaphore);
}
