#include <QStringList>

#include "global.h"
#include "..\Input\stdin.h"
#include "..\Output\stdout.h"
#include "..\Translate\translate.h"
#include "..\Setting\setting.h"
#include "..\Interface\Dpi\dpi.h"

QApplication *Global::qGuiApplication = NULL;
MainWindow *Global::qMainWindow = NULL;
LoopThread *Global::inputLoopThreadAddress = NULL;
ReadFile *Global::readFileLoopThreadAddress = NULL;
TrayIcon *Global::trayIconInstanceAddress = new TrayIcon();

void Global::init(int argc, char *argv[])
{
    // QApplication
    qGuiApplication = new QApplication(argc, argv);
    auto commandLineArguments = QApplication::arguments();

    StdIn::init();

    StdOut::init();

    Translate::init();

    Setting::init(argc, commandLineArguments);

    Dpi::init();

    // Get default font copy
    auto defaultFont = Global::qGuiApplication->font();

    // Update font size
    defaultFont.setPixelSize(Dpi::defaultFontSize_pixel);

    // If value was given, update font family
    auto getFontFamily = Setting::getString("Instance", "Font", Setting::setting);
    if (getFontFamily != "<default>")
    {
        defaultFont.setFamily(getFontFamily);
    }

    // Update default font
    Global::qGuiApplication->setFont(defaultFont);

    // ReadFile thread instance
    readFileLoopThreadAddress = new ReadFile();

    trayIconInstanceAddress->init();

    // MainWindow
    qMainWindow = new MainWindow();
}
