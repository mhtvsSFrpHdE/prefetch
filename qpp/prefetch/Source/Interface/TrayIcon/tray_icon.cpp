#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QWidgetAction>
#include <string>
#include <iostream>

#include "..\..\Global\global.h"
#include "..\..\Input\stdin.h"
#include "..\..\Setting\setting.h"

QSystemTrayIcon *TrayIcon::systemTrayIcon = NULL;

namespace TrayIconObject
{
    QMenu *qMenu = NULL;
    QLabel *instanceNameLabel = NULL;
    QWidgetAction *instanceNameSeparator = NULL;
    QLabel *lastKnownLineLabel = NULL;
    QWidgetAction *lastKnownLineSeparator = NULL;
    QAction *pauseMenu = NULL;
    QAction *resumeMenu = NULL;
    QAction *exitMenu = NULL;
    // Test code
#if TEST_TRAY_MENU_ENABLED
    QAction *testMenu = NULL;
#endif
}

void TrayIcon::init()
{
    using namespace TrayIconObject;

    TrayIcon::systemTrayIcon = new QSystemTrayIcon(Global::qGuiApplication);

    qMenu = new QMenu();

    // Get instance name
    auto instanceName = Setting::getString("Instance", "Name", Setting::setting);

    // Text may not show when mouse hover in newer operating system
    // https://bugreports.qt.io/browse/QTBUG-18821
    systemTrayIcon->setToolTip(instanceName);

    // Tray menu content

    // Show instance name, a seperator with text
    // https://stackoverflow.com/questions/37976696/why-qmenus-separator-doesnt-show-text
    instanceNameLabel = new QLabel(instanceName);
    instanceNameSeparator = new QWidgetAction(systemTrayIcon);
    instanceNameSeparator->setDefaultWidget(instanceNameLabel);
    qMenu->addAction(instanceNameSeparator);

    pauseMenu = new QAction("Pause", qMenu);
    connect(pauseMenu, SIGNAL(triggered()), this, SLOT(action_pause()));
    qMenu->addAction(pauseMenu);

    resumeMenu = new QAction("Resume", qMenu);
    connect(resumeMenu, SIGNAL(triggered()), this, SLOT(action_resume()));
    qMenu->addAction(resumeMenu);

    exitMenu = new QAction("Exit", qMenu);
    connect(exitMenu, SIGNAL(triggered()), this, SLOT(action_exit()));
    qMenu->addAction(exitMenu);


    // Test code entry
#if TEST_TRAY_MENU_ENABLED
    testMenu = new QAction("Test", qMenu);
    connect(testMenu, SIGNAL(triggered()), this, SLOT(action_test()));
    qMenu->addAction(testMenu);
#endif

    systemTrayIcon->setContextMenu(qMenu);

    // Double click show/hide console window
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(action_traydc(QSystemTrayIcon::ActivationReason)));
}

void TrayIcon::start()
{
    TrayIcon::systemTrayIcon->setIcon(QIcon(":/qrc/Resource/icon/main/prefetch.png"));
    TrayIcon::systemTrayIcon->show();
}

void TrayIcon::stop()
{
    TrayIcon::systemTrayIcon->hide();
}

namespace ConsoleCommandFunction
{
    // Actually is not stdin, but behaves very similarly
    void sendTextToStdIn(QString text)
    {
        Global::inputLoopThreadAddress->receiveText(text);
    }
}

void TrayIcon::action_pause()
{
    ConsoleCommandFunction::sendTextToStdIn("pause");
}
void TrayIcon::action_resume()
{
    ConsoleCommandFunction::sendTextToStdIn("resume");
}
void TrayIcon::action_exit()
{
    ConsoleCommandFunction::sendTextToStdIn("exit");
}
void TrayIcon::action_traydc(QSystemTrayIcon::ActivationReason activationReason)
{
    if (activationReason == QSystemTrayIcon::ActivationReason::DoubleClick)
    {
        ConsoleCommandFunction::sendTextToStdIn("traydc");
    }
}
void TrayIcon::action_test()
{
    ConsoleCommandFunction::sendTextToStdIn("test");
}
