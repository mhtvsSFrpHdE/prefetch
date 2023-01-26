#ifndef TrayIconObject_h
#define TrayIconObject_h

#include <QMenu>
#include <QLabel>
#include <QWidgetAction>

#include "Action\custom_action.h"

namespace TrayIconObject
{
    extern QMenu *qMenu;
    extern QLabel *instanceNameLabel;
    extern QWidgetAction *instanceNameSeparator;
    extern QLabel *lastKnownLineLabel;
    extern QWidgetAction *lastKnownLineSeparator;
    extern QAction *stopMenu;
    extern QAction *startMenu;
    extern QAction *exitMenu;
    extern QList<CustomAction *> *customAction;
    // Test code
#if TEST_TRAY_MENU_ENABLED
    extern QAction *testMenu;
#endif
}

#endif
