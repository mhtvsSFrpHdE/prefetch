#include <QCoreApplication>
#include <QStringList>

#include "global.h"
#include "..\Output\stdout.h"
#include "..\Translate\translate.h"
#include "..\Setting\setting.h"

QCoreApplication *Global::qCoreApplication;

void Global::init(int argc, char *argv[])
{
    // QCoreApplication
    qCoreApplication = new QCoreApplication(argc, argv);
    auto commandLineArguments = QCoreApplication::arguments();

    StdOut::init();

    Translate::init();

    Setting::init(argc, commandLineArguments);
}
