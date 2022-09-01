#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QWidgetAction>
#include <string>
#include <iostream>

#include "..\..\Global\global.h"
#include "..\..\Input\stdin.h"
#include "..\..\Setting\setting.h"
#include "..\Dpi\dpi.h"
#include "..\..\Define\define.h"

QSystemTrayIcon *TrayIcon::systemTrayIcon = NULL;

const int defaultMenuWdith = 100;
const int defaultLabelPadding = 10;

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
    connect(instanceNameSeparator, SIGNAL(triggered()), this, SLOT(action_traydc_void()));
    qMenu->addAction(instanceNameSeparator);

    // Show last known line of stdout, a seperator with text
    lastKnownLineLabel = new QLabel();
    lastKnownLineSeparator = new QWidgetAction(systemTrayIcon);
    lastKnownLineSeparator->setDefaultWidget(lastKnownLineLabel);
    connect(lastKnownLineSeparator, SIGNAL(triggered()), this, SLOT(action_traydc_void()));
    qMenu->addAction(lastKnownLineSeparator);

    pauseMenu = new QAction("Pause", qMenu);
    connect(pauseMenu, SIGNAL(triggered()), this, SLOT(action_pause()));
    qMenu->addAction(pauseMenu);

    resumeMenu = new QAction("Resume", qMenu);
    connect(resumeMenu, SIGNAL(triggered()), this, SLOT(action_resume()));
    qMenu->addAction(resumeMenu);

    exitMenu = new QAction("Exit", qMenu);
    connect(exitMenu, SIGNAL(triggered()), this, SLOT(action_exit()));
    qMenu->addAction(exitMenu);

    // Menu style
    qMenu->setFixedWidth(Dpi::multiply(defaultMenuWdith));

    // Test code entry
#if TEST_TRAY_MENU_ENABLED
    testMenu = new QAction("Test", qMenu);
    connect(testMenu, SIGNAL(triggered()), this, SLOT(action_test()));
    qMenu->addAction(testMenu);
#endif

    systemTrayIcon->setContextMenu(qMenu);

    // Event

    // Update content before show right click menu
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(action_updateMenu(QSystemTrayIcon::ActivationReason)));
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
void TrayIcon::action_traydc_void()
{
    ConsoleCommandFunction::sendTextToStdIn("traydc");
}
void TrayIcon::action_test()
{
    ConsoleCommandFunction::sendTextToStdIn("test");
}
void TrayIcon::action_updateMenu(QSystemTrayIcon::ActivationReason activationReason)
{
    using namespace TrayIconObject;

    if (activationReason == QSystemTrayIcon::ActivationReason::Context)
    {
        // Update last known line text

        // Ignore new line from result
        auto lastKnownLine = Global::qMainWindow->lastKnownLine.trimmed();

        // Set to label
        lastKnownLineLabel->setMinimumWidth(0);
        lastKnownLineLabel->setText(lastKnownLine);
        lastKnownLineLabel->adjustSize();

        // Calculate minimal menu width

        // Get width from unchanged widget
        auto newMenuWidth = Dpi::multiply(defaultMenuWdith);
        auto lastKnownLineLabelWidth = lastKnownLineLabel->width();
        newMenuWidth = defaultMenuWdith >= lastKnownLineLabelWidth ? defaultMenuWdith
                                                                   : lastKnownLineLabelWidth;
        // Add label padding to total width
        newMenuWidth = newMenuWidth + Dpi::multiply(defaultLabelPadding);

        // Apply width to menu
        qMenu->setFixedWidth(newMenuWidth);
        // qMenu->adjustSize();
    }
}
