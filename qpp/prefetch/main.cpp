#include <QStringList>

#include "Source\Global\global.h"
#include "Source\Output\stdout.h"
#include "Source\Translate\translate.h"
#include "Source\Setting\setting.h"

int main(int argc, char *argv[])
{
    Global::init(argc, argv);

    auto configGroups = Setting::setting->childGroups();

    foreach (auto rootGroupName, configGroups)
    {
        Setting::setting->beginGroup(rootGroupName);
        *StdOut::consoleOutput << rootGroupName
                               << endl;

        auto configKeys = Setting::setting->childKeys();
        foreach (auto configKey, configKeys)
        {
            *StdOut::consoleOutput << Setting::setting->value(configKey).toString()
                                   << endl;
        }

        Setting::setting->endGroup();
    };

    return 0;
}
