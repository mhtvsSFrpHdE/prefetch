#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QStringList>
#include <QTextStream>

#include "Source\Setting\setting.h"

QTextStream out(stdout);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "prefetch_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

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
