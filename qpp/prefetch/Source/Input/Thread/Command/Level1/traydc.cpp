#include <QTimer>

#include "parent_define.h"
#include "..\..\..\..\Global\global.h"

void Parent_Prefetch::traydc()
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
