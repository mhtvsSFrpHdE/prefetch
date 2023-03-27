#include "tray_icon_object.h"
#include "../../Define/define.h"

namespace TrayIconObject
{
    QMenu *qMenu = NULL;
    QLabel *instanceNameLabel = NULL;
    QWidgetAction *instanceNameSeparator = NULL;
    QLabel *lastKnownLineLabel = NULL;
    QWidgetAction *lastKnownLineSeparator = NULL;
    QAction *stopMenu = NULL;
    QAction *startMenu = NULL;
    QAction *exitMenu = NULL;
    QList<CustomAction *> *customAction = NULL;
    // Test code
#if TEST_TRAY_MENU_ENABLED
    QAction *testMenu = NULL;
#endif
}
