#include <QLocale>
#include <QStringList>

#include "translate.h"
#include "..\Global\global.h"

QTranslator *Translate::translator;

void Translate::init()
{
    translator = new QTranslator();

    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "prefetch_" + QLocale(locale).name();
        if (translator->load(":/i18n/" + baseName))
        {
            Global::qGuiApplication->installTranslator(translator);
            break;
        }
    }
}
