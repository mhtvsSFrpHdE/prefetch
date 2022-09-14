#include <QStringList>

#include "global.h"
#include "..\Input\stdin.h"
#include "..\Output\stdout.h"
#include "..\Translate\translate.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"
#include "..\Interface\Dpi\dpi.h"
#include "..\Core\scan_cache.h"
#include "..\Define\define.h"
#include "..\Output\log.h"

QApplication *Global::qGuiApplication = NULL;
MainWindow *Global::qMainWindow = NULL;
LoopThread *Global::inputLoopThreadAddress = NULL;
ReadFile *Global::readFileLoopThreadAddress = NULL;
TrayIcon *Global::trayIconInstanceAddress = new TrayIcon();

void Global::init(int argc, char *argv[])
{
    using namespace Const_Setting;
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Instance_ConfigKeyName;

    // QApplication
    qGuiApplication = new QApplication(argc, argv);
    auto commandLineArguments = QApplication::arguments();

    StdIn::init();

    StdOut::init();

    Translate::init();

    Setting::init(argc, commandLineArguments);

    ScanCache::init(argc, commandLineArguments);

#if LOG_ENABLED
    Log::init(argc, commandLineArguments);
#endif

    Dpi::init();

    // Get default font copy
    auto defaultFont = Global::qGuiApplication->font();

    // Update font size
    defaultFont.setPixelSize(Dpi::defaultFontSize_pixel);

    // If value was given, update font family
    auto getFontFamily = Setting::getString(Instance, Font, Setting::setting);
    if (getFontFamily != Font_Value::Default)
    {
        defaultFont.setFamily(getFontFamily);
    }

    // Update default font
    Global::qGuiApplication->setFont(defaultFont);

    // ReadFile thread instance
    readFileLoopThreadAddress = new ReadFile();

    // Tray icon
    trayIconInstanceAddress->init();

    // MainWindow
    qMainWindow = new MainWindow();
}
