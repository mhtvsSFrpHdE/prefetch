#ifndef Const_Tray_Icon_h
#define Const_Tray_Icon_h

#include <QString>

namespace Const_TrayIcon
{
    const int DefaultLabelPadding = 10;

    namespace Resource
    {
        const QString QIconPath = ":/qrc/Resource/icon/main/prefetch.png";
    }
    namespace MenuText
    {
        extern QString Stop;
        extern QString Start;
        extern QString Exit;

        // Test code entry
#if TEST_TRAY_MENU_ENABLED
        const QString Test = "Test";
#endif

        extern void init();

        // See translate_define.h for more information
        extern void tdummy();
    }
}

#endif
