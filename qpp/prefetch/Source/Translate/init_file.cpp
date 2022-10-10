#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include <QStringList>

#include "translator_loader.h"
#include "..\Global\global.h"

// If false, translate file is not loaded, related install is ignored
bool loadTranslate_load_tryInstall(QTranslator *translator, QString translateFileName, QString translateFolder)
{
    if (translator->load(translateFileName, translateFolder))
    {
        // Load success
        // Install translator to global
        Global::qGuiApplication->installTranslator(translator);

        return true;
    }
    return false;
}

// Load translate file, install if success
bool loadTranslate_load(
    QTranslator *translator,
    QStringList uiLanguages,
    QString translateName,
    QString translateFolder,
    QString translateFileSuffix)
{

    // Confirm translate exist
    bool translateNotFound = true;
    for (const QString &locale : uiLanguages)
    {
        // prefetch_en_US.qm
        QString translateFileName = translateName + "_" + QLocale(locale).name() + translateFileSuffix;
        translateFileName = translateName + "_" + QLocale::system().name() + translateFileSuffix;

        // Try install
        bool installResult = loadTranslate_load_tryInstall(translator, translateFileName, translateFolder);
        if (installResult)
        {
            // Load and install success
            translateNotFound = false;
            break;
        }
    }
    // Translate not found, use fallback file
    if (translateNotFound)
    {
        // Fallback to English
        // If still fails, program should not continue to run
        const QString translateFileNameFallback = translateName + "_en_US.qm";
        return loadTranslate_load_tryInstall(translator, translateFileNameFallback, translateFolder);
    }
    // Translate found and installed
    else
    {
        return true;
    }
}

// prefetch/translations/qt
// prefetch/translations/prefetch
QString loadTranslate_getTranslateFolder(QString qtPathSplitter, QString translateName)
{
    return Global::qGuiApplication->applicationDirPath() + qtPathSplitter + "translations" + qtPathSplitter + translateName;
}

bool loadTranslate(QString translateName, QStringList uiLanguages, QString qtPathSplitter, QString translateFileSuffix)
{
    QTranslator qTranslator;
    auto translateFolder = loadTranslate_getTranslateFolder(qtPathSplitter, translateName);

    return loadTranslate_load(&qTranslator, uiLanguages, translateName, translateFolder, translateFileSuffix);
}

void TranslatorLoader::initFile()
{
    const QString qtPathSplitter = "/";
    const QString translateFileSuffix = ".qm";
    auto uiLanguages = QLocale::system().uiLanguages();

    // Qt translate
    // Fail safe, no translation provided in Qt 4.8.7 installation
    loadTranslate("qt", uiLanguages, qtPathSplitter, translateFileSuffix);

    // Prefetch translate
    bool loadSuccess = loadTranslate("prefetch", uiLanguages, qtPathSplitter, translateFileSuffix);
    if (loadSuccess == false)
    {
        throw;
    }
}
