#include "tray_icon.h"
#include "tray_icon_object.h"
#include "const_tray_icon.h"
#include "..\..\Global\global.h"
#include "..\..\Input\stdin.h"
#include "..\..\Input\const_input.h"
#include "..\Dpi\dpi.h"

QSystemTrayIcon *TrayIcon::systemTrayIcon = NULL;

int TrayIcon::trayMenuMinimalWidth;

// Test code
#if TEST_TRAY_MENU_ENABLED
static QAction *testMenu;
#endif

void TrayIcon::reloadTranslate()
{
    using namespace TrayIconObject;
    using namespace Const_TrayIcon;

    stopMenu->setText(MenuText::Stop);
    startMenu->setText(MenuText::Start);
    exitMenu->setText(MenuText::Exit);
}

void TrayIcon::start()
{
    using namespace Const_TrayIcon::Resource;
    systemTrayIcon->setIcon(QIcon(QIconPath));
    systemTrayIcon->show();
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
    using namespace Const_TrayIcon;
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
        newMenuWidth = newMenuWidth + Dpi::multiply(DefaultLabelPadding);

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
