#include <QStringList>

#include "global.h"
#include "../Input/stdin.h"
#include "../Output/stdout.h"
#include "../Translate/translator_loader.h"
#include "../Setting/const_setting.h"
#include "../Interface/Dpi/dpi.h"
#include "../ReadLoop/ScanCache/scan_cache.h"
#include "../ReadLoop/Startup/startup.h"
#include "../ReadLoop/Skip/skip.h"
#include "../ReadLoop/RocketLaunch/rocket_launch.h"
#include "../ReadLoop/ReadFile/read_file_thread.h"
#include "../Define/define.h"
#include "../Output/log.h"

QApplication *Global::qGuiApplication = NULL;
RunOnUiThreadExample *Global::runOnUiThreadAddress = NULL;
MainWindow *Global::qMainWindow = NULL;
InputLoopThread *Global::inputLoopThreadAddress = NULL;
ReadLoop *Global::readLoopThreadAddress = NULL;
TrayIcon *Global::trayIconInstanceAddress = NULL;
CommandLineArgument *Global::commandLineArgumentAddress = NULL;
Setting *Global::qSettingAddress = NULL;
WindowsIniExample *Global::windowsIniExampleAddress = NULL;

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

    WindowsIniExample *windowsIniExample = new WindowsIniExample();
    windowsIniExample->init();
    windowsIniExampleAddress = windowsIniExample;
    LAST_KNOWN_POSITION(2)

    qSettingAddress = new Setting();
    Setting::init();
    LAST_KNOWN_POSITION(2)

#if TRANSLATE_ENABLED
    TranslatorLoader::initFile();
    LAST_KNOWN_POSITION(2)
    TranslatorLoader::initMessage();
    LAST_KNOWN_POSITION(2)
#endif

    ReadLoop_Startup::init();
    LAST_KNOWN_POSITION(2)

    ReadLoop_Skip::init();
    LAST_KNOWN_POSITION(2)

    ReadLoop_RocketLaunch::init();
    LAST_KNOWN_POSITION(2)

    ReadLoop_ScanCache::init();
    LAST_KNOWN_POSITION(2)

    Dpi::init();
    LAST_KNOWN_POSITION(2)

    // Get default font copy
    auto defaultFont = Global::qGuiApplication->font();

    // Update font size
    defaultFont.setPixelSize(Dpi::defaultFontSize_pixel);

    // If value was given, update font family
#if SKIP_CUSTOM_FONT == false
    auto getFontFamily = Setting::getString(gn::Instance, ikn::Font, Setting::setting);
    if (getFontFamily != ifv::Default)
    {
        defaultFont.setFamily(getFontFamily);
    }
    LAST_KNOWN_POSITION(2)
#endif

    // Update default font
    Global::qGuiApplication->setFont(defaultFont);

    // ReadThread
    ReadLoop_ReadFileThread::init();

    // ReadFile thread instance
    readLoopThreadAddress = new ReadLoop();
    LAST_KNOWN_POSITION(2)

    // Tray icon
    trayIconInstanceAddress = new TrayIcon();
    trayIconInstanceAddress->init();
    LAST_KNOWN_POSITION(2)

    // MainWindow
    qMainWindow = new MainWindow();
    LAST_KNOWN_POSITION(1)
}
