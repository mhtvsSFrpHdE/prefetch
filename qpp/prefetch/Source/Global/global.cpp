#include <QStringList>

#include "global.h"
#include "..\Input\stdin.h"
#include "..\Output\stdout.h"
#include "..\Translate\translator_loader.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"
#include "..\Interface\Dpi\dpi.h"
#include "..\Core\ScanCache\scan_cache.h"
#include "..\Core\Startup\startup.h"
#include "..\Core\Skip\skip.h"
#include "..\Core\ReadFile\read_file_thread.h"
#include "..\Define\define.h"
#include "..\Output\log.h"

QApplication *Global::qGuiApplication = NULL;
RunOnUiThreadExample *Global::runOnUiThreadAddress = NULL;
MainWindow *Global::qMainWindow = NULL;
InputLoopThread *Global::inputLoopThreadAddress = NULL;
Core *Global::coreLoopThreadAddress = NULL;
TrayIcon *Global::trayIconInstanceAddress = NULL;
CommandLineArgument *Global::commandLineArgumentAddress = NULL;

#define gn Const_Setting::ConfigGroupName
#define ikn Const_Setting::ConfigKeyName::Instance
#define ifv Const_Setting::Value::Instance::Font

void Global::init(int argc, char *argv[])
{
    // QApplication
    qGuiApplication = new QApplication(argc, argv);
    runOnUiThreadAddress = new RunOnUiThreadExample();
    runOnUiThreadAddress->init();

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

    Core_Startup::init();
    LAST_KNOWN_POSITION(2)

    // Skip
    Core_Skip::init();
    LAST_KNOWN_POSITION(2)

    Core_ScanCache::init();
    LAST_KNOWN_POSITION(2)

    Dpi::init();
    LAST_KNOWN_POSITION(2)

    // Get default font copy
    auto defaultFont = Global::qGuiApplication->font();

    // Update font size
    defaultFont.setPixelSize(Dpi::defaultFontSize_pixel);

    // If value was given, update font family
    auto getFontFamily = Setting::getString(gn::Instance, ikn::Font, Setting::setting);
    if (getFontFamily != ifv::Default)
    {
        defaultFont.setFamily(getFontFamily);
    }
    LAST_KNOWN_POSITION(2)

    // Update default font
    Global::qGuiApplication->setFont(defaultFont);

    // ReadThread
    Core_ReadFileThread::init();

    // ReadFile thread instance
    coreLoopThreadAddress = new Core();
    LAST_KNOWN_POSITION(2)

    // Tray icon
    trayIconInstanceAddress = new TrayIcon();
    trayIconInstanceAddress->init();
    LAST_KNOWN_POSITION(2)

    // MainWindow
    qMainWindow = new MainWindow();
    LAST_KNOWN_POSITION(1)
}
