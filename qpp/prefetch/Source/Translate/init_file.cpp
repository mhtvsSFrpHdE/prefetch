#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include <QStringList>

#include "translator_loader.h"
#include "..\Global\global.h"

void TranslatorLoader::initFile()
{
    QString qtPathSplitter = "/";

    auto qtTranslateFileName = "qt_" + QLocale::system().name();
    auto qtTranslateFilePath = Global::qGuiApplication->applicationDirPath() + qtPathSplitter + "translations/qt";

    QTranslator qtTranslator;
    qtTranslator.load(qtTranslateFileName,
                      qtTranslateFilePath);
    Global::qGuiApplication->installTranslator(&qtTranslator);

    auto prefetchTranslateFileName = "prefetch_" + QLocale::system().name();
    auto prefetchTranslateFilePath = Global::qGuiApplication->applicationDirPath() + qtPathSplitter + "translations/prefetch";

    QTranslator prefetchTranslator;
    prefetchTranslator.load(prefetchTranslateFileName, prefetchTranslateFilePath);
    Global::qGuiApplication->installTranslator(&prefetchTranslator);

    // Global::translatorAddress = new QTranslator();

    // const QStringList uiLanguages = QLocale::system().uiLanguages();

    // for (const QString &locale : uiLanguages)
    // {
    //     const QString baseName = "prefetch_" + QLocale(locale).name();
    //     if (Global::translatorAddress->load(":/i18n/" + baseName))
    //     {
    //         Global::qGuiApplication->installTranslator(Global::translatorAddress);
    //         break;
    //     }
    // }
}
