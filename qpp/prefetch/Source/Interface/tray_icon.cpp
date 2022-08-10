#include "tray_icon.h"
#include "..\Global\global.h"

QSystemTrayIcon *TrayIcon::systemTrayIcon = NULL;

void TrayIcon::init()
{
    TrayIcon::systemTrayIcon = new QSystemTrayIcon(Global::qGuiApplication);
}

void TrayIcon::start()
{
    TrayIcon::systemTrayIcon->setIcon(QIcon(":/qrc/Resource/icon/main/prefetch.png"));
    TrayIcon::systemTrayIcon->show();
}
