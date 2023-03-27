#include <QTimer>

#include "parent_define.h"
#include "../../../../Global/global.h"

void traydc_hide()
{
    Global::qMainWindow->hide();
}

void traydc_show()
{
    // Restore and bring to front
    Global::qMainWindow->show();
    QTimer::singleShot(0, Global::qMainWindow, SLOT(restored_slot()));
}

void Parent_Prefetch::traydc()
{
    auto mainWindowVisible = Global::qMainWindow->isVisible();
    if (mainWindowVisible)
    {
        Global::runOnUiThreadAddress->run_block(&traydc_hide);
    }
    else
    {
        Global::runOnUiThreadAddress->run_block(&traydc_show);
    }
}
