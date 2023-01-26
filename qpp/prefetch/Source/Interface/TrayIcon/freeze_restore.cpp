#include "tray_icon.h"
#include "tray_icon_object.h"
// #include "..\MainWindow\mainwindow.h"

void TrayIcon::freeze()
{
    using namespace TrayIconObject;

    stopMenu->setEnabled(false);
    startMenu->setEnabled(false);
}

void TrayIcon::restore()
{
    using namespace TrayIconObject;

    stopMenu->setEnabled(true);
    startMenu->setEnabled(true);
}
