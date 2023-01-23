#include <QStringList>

#include "global.h"
#include "..\Example\Hack\function_pointer_in_signal_slot.h"
#include "..\Input\stdin.h"
#include "..\Output\stdout.h"
#include "..\Translate\translator_loader.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"
#include "..\Interface\Dpi\dpi.h"
#include "..\Core\scan_cache.h"
#include "..\Define\define.h"
#include "..\Output\log.h"
#include "..\Core\startup.h"
#include "..\Core\Thread\Read\read_thread.h"

QApplication *Global::qGuiApplication = NULL;
MainWindow *Global::qMainWindow = NULL;
InputLoopThread *Global::inputLoopThreadAddress = NULL;
ReadFile *Global::readFileLoopThreadAddress = NULL;
TrayIcon *Global::trayIconInstanceAddress = NULL;
CommandLineArgument *Global::commandLineArgumentAddress = NULL;

void Global::init(int argc, char *argv[])
{
    using namespace Const_Setting;
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Instance_ConfigKeyName;

    // QApplication
    qGuiApplication = new QApplication(argc, argv);
    MocFunctionPointer::init();

    // Command line argument
    auto argvQStringList = QApplication::arguments();

#if LOG_ENABLED
    Log::init(argc, argvQStringList);
#endif
    LAST_KNOWN_POSITION(0)

    commandLineArgumentAddress = new CommandLineArgument(argc, argvQStringList);

    StdIn::init();
    LAST_KNOWN_POSITION(2)

    StdOut::init();
    LAST_KNOWN_POSITION(2)

    Setting::init();
    LAST_KNOWN_POSITION(2)

#if TRANSLATE_ENABLED
    TranslatorLoader::initFile();
    LAST_KNOWN_POSITION(2)
    TranslatorLoader::initMessage();
    LAST_KNOWN_POSITION(2)
#endif

    Startup::init();
    LAST_KNOWN_POSITION(2)

    ScanCache::init();
    LAST_KNOWN_POSITION(2)

    Dpi::init();
    LAST_KNOWN_POSITION(2)

    // Get default font copy
    auto defaultFont = Global::qGuiApplication->font();

    // Update font size
    defaultFont.setPixelSize(Dpi::defaultFontSize_pixel);

    // If value was given, update font family
    auto getFontFamily = Setting::getString(Instance, Font, Setting::setting);
    if (getFontFamily != Instance_Font_Value::Default)
    {
        defaultFont.setFamily(getFontFamily);
    }
    LAST_KNOWN_POSITION(2)

    // Update default font
    Global::qGuiApplication->setFont(defaultFont);

    // ReadThread
    ReadThread::init();

    // ReadFile thread instance
    readFileLoopThreadAddress = new ReadFile();
    LAST_KNOWN_POSITION(2)

    // Tray icon
    trayIconInstanceAddress = new TrayIcon();
    trayIconInstanceAddress->init();
    LAST_KNOWN_POSITION(2)

    // MainWindow
    qMainWindow = new MainWindow();
    LAST_KNOWN_POSITION(1)
}
