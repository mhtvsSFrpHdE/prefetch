#include <QTimer>

#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Global\global.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::traydc()
{
    auto mainWindowVisible = Global::qMainWindow->isVisible();
    if (mainWindowVisible)
    {
        Global::qMainWindow->hide();
    }
    else
    {
        // Restore and bring to front
        Global::qMainWindow->show();
        QTimer::singleShot(0, Global::qMainWindow, SLOT(restored_slot()));
    }
}
