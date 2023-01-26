#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QWidgetAction>
#include <string>
#include <iostream>
#include <QList>

#include "..\..\Global\global.h"
#include "..\..\Input\stdin.h"
#include "..\..\Input\const_input.h"
#include "..\..\Setting\setting.h"
#include "..\..\Setting\const_setting.h"
#include "..\Dpi\dpi.h"
#include "..\..\Define\define.h"
#include "const_tray_icon.h"
#include "Action\custom_action.h"

QSystemTrayIcon *TrayIcon::systemTrayIcon = NULL;

int trayMenuMinimalWidth;
const int defaultLabelPadding = 10;

void TrayIcon::init()
{
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Instance_ConfigKeyName;
    using namespace TrayIconObject;
    using namespace Const_TrayIcon;

    TrayIcon::systemTrayIcon = new QSystemTrayIcon(Global::qGuiApplication);

    qMenu = new QMenu();

    // Get instance name
    auto instanceName = Setting::getString(Instance, Name, Setting::setting);

    // Text may not show when mouse hover in newer operating system
    // https://bugreports.qt.io/browse/QTBUG-18821
    systemTrayIcon->setToolTip(instanceName);

    // Get default menu width
    auto getTrayMenuMinimalWidth = Setting::getInt(Instance, TrayMenuMinimalWidth, Setting::setting);
    trayMenuMinimalWidth = getTrayMenuMinimalWidth.result;

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

    // Custom tray menu
    customAction = new QList<CustomAction *>();

    // Get custom tray menu
    auto getCustomTrayMenu = Setting::getArray(CustomTrayMenu, Setting::setting);

    // Find key value pair if exist
    auto customTrayMenuName = getCustomTrayMenu.keys();
    for (int i = 0; i < customTrayMenuName.size(); ++i)
    {
        auto menuName = customTrayMenuName[i];
        auto menuCommand = getCustomTrayMenu[menuName];

        // Create action
        auto customMenu = new CustomAction(menuName, qMenu);
        customMenu->init(new QString(menuCommand), &action_custom);
        connect(customMenu, SIGNAL(triggered()), customMenu, SLOT(triggered_slot()));
        qMenu->addAction(customMenu);

        // Save action
        customAction->append(customMenu);
    }

    // Other standard tray menu

    stopMenu = new QAction(MenuText::Stop, qMenu);
    connect(stopMenu, SIGNAL(triggered()), this, SLOT(action_stop()));
    qMenu->addAction(stopMenu);

    startMenu = new QAction(MenuText::Start, qMenu);
    connect(startMenu, SIGNAL(triggered()), this, SLOT(action_start()));
    qMenu->addAction(startMenu);

    exitMenu = new QAction(MenuText::Exit, qMenu);
    connect(exitMenu, SIGNAL(triggered()), this, SLOT(action_exit()));
    qMenu->addAction(exitMenu);

    // Test code entry
#if TEST_TRAY_MENU_ENABLED
    testMenu = new QAction(MenuText::Test, qMenu);
    connect(testMenu, SIGNAL(triggered()), this, SLOT(action_test()));
    qMenu->addAction(testMenu);
#endif

    // Menu style
    qMenu->setFixedWidth(Dpi::multiply(trayMenuMinimalWidth));

    systemTrayIcon->setContextMenu(qMenu);

    // Event

    // Update content before show right click menu
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(action_updateMenu(QSystemTrayIcon::ActivationReason)));
    // Double click show/hide console window
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(action_traydc(QSystemTrayIcon::ActivationReason)));
}

void TrayIcon::reloadTranslate()
{
    using namespace Const_TrayIcon;

    TrayIconObject::stopMenu->setText(MenuText::Stop);
    TrayIconObject::startMenu->setText(MenuText::Start);
    TrayIconObject::exitMenu->setText(MenuText::Exit);
}

void TrayIcon::start()
{
    using namespace Const_TrayIcon::Resource;
    TrayIcon::systemTrayIcon->setIcon(QIcon(QIconPath));
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

using namespace Const_Input;
void TrayIcon::action_stop()
{
    ConsoleCommandFunction::sendTextToStdIn(Command_Level1::stop);
}
void TrayIcon::action_start()
{
    ConsoleCommandFunction::sendTextToStdIn(Command_Level1::start);
}
void TrayIcon::action_exit()
{
    ConsoleCommandFunction::sendTextToStdIn(Command_Level1::exit);
}
void TrayIcon::action_traydc(QSystemTrayIcon::ActivationReason activationReason)
{
    if (activationReason == QSystemTrayIcon::ActivationReason::DoubleClick)
    {
        ConsoleCommandFunction::sendTextToStdIn(Command_Level1::traydc);
    }
}
void TrayIcon::action_traydc_void()
{
    ConsoleCommandFunction::sendTextToStdIn(Command_Level1::traydc);
}
void TrayIcon::action_test()
{
    ConsoleCommandFunction::sendTextToStdIn(Command_Level1::test);
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
        auto newMenuWidth = Dpi::multiply(trayMenuMinimalWidth);
        auto lastKnownLineLabelWidth = lastKnownLineLabel->width();
        newMenuWidth = trayMenuMinimalWidth >= lastKnownLineLabelWidth ? trayMenuMinimalWidth
                                                                       : lastKnownLineLabelWidth;
        // Add label padding to total width
        newMenuWidth = newMenuWidth + Dpi::multiply(defaultLabelPadding);

        // Apply width to menu
        // The reason to use fixed width is QSystemTrayIcon behave different than a regular widget
        //     It will not response to `setMinimumWidth()` or combine with `update()` anymore after the first one
        //     at least in Qt 4.8.7
        qMenu->setFixedWidth(newMenuWidth);
    }
}
void TrayIcon::action_custom(void *command)
{
    using namespace Command_Level2;

    auto commandAsQStringAddress = (QString *)command;
    QString commandAsQString = run_withSplitter + *commandAsQStringAddress;

    ConsoleCommandFunction::sendTextToStdIn(commandAsQString);
}
