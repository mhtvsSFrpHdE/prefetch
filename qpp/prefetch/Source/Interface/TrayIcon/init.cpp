#include <QMenu>

#include "tray_icon.h"
#include "tray_icon_object.h"
#include "..\..\Global\global.h"
#include "..\..\Setting\setting.h"
#include "..\..\Setting\const_setting.h"
#include "const_tray_icon.h"
#include "..\Dpi\dpi.h"

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

    // Test code entry
#if TEST_TRAY_MENU_ENABLED
    testMenu = new QAction(MenuText::Test, qMenu);
    connect(testMenu, SIGNAL(triggered()), this, SLOT(action_test()));
    qMenu->addAction(testMenu);
#endif

    // Exit always at bottom
    exitMenu = new QAction(MenuText::Exit, qMenu);
    connect(exitMenu, SIGNAL(triggered()), this, SLOT(action_exit()));
    qMenu->addAction(exitMenu);

    // Menu style
    qMenu->setFixedWidth(Dpi::multiply(trayMenuMinimalWidth));

    systemTrayIcon->setContextMenu(qMenu);

    // Event

    // Update content before show right click menu
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(action_updateMenu(QSystemTrayIcon::ActivationReason)));
    // Double click show/hide console window
    connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(action_traydc(QSystemTrayIcon::ActivationReason)));
}
