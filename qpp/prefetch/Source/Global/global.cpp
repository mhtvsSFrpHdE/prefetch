#include <QCoreApplication>

#include "global.h"
#include "..\Output\stdout.h"
#include "..\Translate\translate.h"
#include "..\Setting\setting.h"

QCoreApplication *Global::qCoreApplication;

void Global::init(int argc, char *argv[])
{
    qCoreApplication = new QCoreApplication(argc, argv);

    StdOut::init();

    Translate::init();

    Setting::init();
}