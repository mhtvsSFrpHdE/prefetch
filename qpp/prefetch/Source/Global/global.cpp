#include <QStringList>

#include "global.h"
#include "..\Input\stdin.h"
#include "..\Output\stdout.h"
#include "..\Translate\translate.h"
#include "..\Setting\setting.h"
#include "..\Interface\tray_icon.h"

QApplication *Global::qGuiApplication = NULL;
LoopThread *Global::inputLoopThreadAddress = NULL;
ReadFile *Global::readFileLoopThreadAddress = NULL;

void Global::init(int argc, char *argv[])
{
    // QApplication
    qGuiApplication = new QApplication(argc, argv);
    auto commandLineArguments = QApplication::arguments();

    StdIn::init();

    StdOut::init();

    Translate::init();

    Setting::init(argc, commandLineArguments);

    // ReadFile thread instance
    readFileLoopThreadAddress = new ReadFile();

    TrayIcon::init();
}
