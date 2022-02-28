#include <QCoreApplication>
#include <QStringList>
#include <QTextStream>

#include "Source\Global\global.h"
#include "Source\Translate\translate.h"
#include "Source\Setting\setting.h"

QTextStream out(stdout);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Global::qCoreApplication = &a;

    Translate::init();

    Setting::init();
    auto configGroups = Setting::setting->childGroups();

    QTextStream consoleOutput(stdout);

    foreach(auto rootGroupName, configGroups)
    {
        Setting::setting->beginGroup(rootGroupName);
        consoleOutput << rootGroupName
            << endl;

        auto configKeys = Setting::setting->childKeys();
        foreach(auto configKey, configKeys)
        {
            consoleOutput << Setting::setting->value(configKey).toString()
                << endl;
        }

        Setting::setting->endGroup();
    };


    return a.exec();
}
