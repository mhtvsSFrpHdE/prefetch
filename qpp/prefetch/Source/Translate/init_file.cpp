#include <QLibraryInfo>
#include <QLocale>
#include <QStringList>
#include <stdexcept>

#include "translator_loader.h"
#include "..\Global\global.h"
#include "..\Output\log.h"
#include "const_translator_loader.h"
#include "..\Setting\setting.h"
#include "..\Setting\const_setting.h"

QList<QTranslator *> TranslatorLoader::installedTranslator = QList<QTranslator *>();

// If false, translate file is not loaded, related install is ignored
bool loadTranslate_load_tryInstall(QTranslator *translator, QString translateFileName, QString translateFolder)
{
    using namespace Const_TranslatorLoader::Message;

    if (translator->load(translateFileName, translateFolder))
    {
        // Load success
        // Install translator to global
        Global::qGuiApplication->installTranslator(translator);

#if LOG_ENABLED
        Log::lock();
        *Log::logTextStream << TranslateLoaded
                            << translateFileName << endl;
        Log::logTextStream->flush();
        Log::unlock();
#endif

        return true;
    }
    return false;
}

// Use language name
// From `prefetch, en_US, .qm` to `prefetch_en_US.qm`
QString loadTranslate_load_getTranslateFile(QString translateName, QString languageName, QString translateFileSuffix)
{
    return translateName + "_" + languageName + translateFileSuffix;
}

// Use system language
// From `prefetch, .qm` to `prefetch_en_US.qm`
QString loadTranslate_load_getTranslateFile(QString translateName, QString translateFileSuffix)
{
    return loadTranslate_load_getTranslateFile(translateName, QLocale::system().name(), translateFileSuffix);
}

// Load translate file, install if success
bool loadTranslate_load(
    QTranslator *translator,
    QString translateName,
    QString translateFolder,
    QString translateFileSuffix,
    QString languageName)
{
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Instance_ConfigKeyName;
    using namespace Const_Setting;

    // In certain case, do not fallback to en_US
    bool noFallback = false;

    // languageName NULL, get from setting
    if (languageName == NULL)
    {
        languageName = Setting::getString(Instance, Language, Setting::setting);
        if (languageName == Instance_Language_Value::Default)
        {
            languageName = loadTranslate_load_getTranslateFile(translateName, translateFileSuffix);
        }
        else
        {
            languageName = loadTranslate_load_getTranslateFile(translateName, languageName, translateFileSuffix);
        }
    }
    else
    {
        noFallback = true;
        languageName = loadTranslate_load_getTranslateFile(translateName, languageName, translateFileSuffix);
    }

    // Confirm translate exist
    bool translateNotFound = true;

    // Try install language
    {
        bool installResult = loadTranslate_load_tryInstall(translator, languageName, translateFolder);
        if (installResult)
        {
            translateNotFound = false;
        }
    }

    // If fail to install and no fallback
    if (noFallback && translateNotFound)
    {
        return false;
    }

    // If fail to install
    // Try install system language
    if (translateNotFound)
    {
        QString translateFileName = translateName + "_" + QLocale::system().name() + translateFileSuffix;

        // Try install
        bool installResult = loadTranslate_load_tryInstall(translator, translateFileName, translateFolder);
        if (installResult)
        {
            // Load and install success
            translateNotFound = false;
        }
    }

    // If fail to install
    // Try use fallback file
    //
    // Last if statement
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

bool loadTranslate(QString translateName, QString qtPathSplitter, QString translateFileSuffix, QString languageName)
{
    // Keep translator in memory
    // https://stackoverflow.com/questions/28509106/translation-not-working-in-qt
    auto qTranslatorAddress = new QTranslator();

    auto translateFolder = loadTranslate_getTranslateFolder(qtPathSplitter, translateName);

    // Get load result
    bool loadSuccess = loadTranslate_load(qTranslatorAddress, translateName, translateFolder, translateFileSuffix, languageName);
    if (loadSuccess)
    {
        // Collect address
        TranslatorLoader::installedTranslator.append(qTranslatorAddress);
    }
    else
    {
        // Free memory
        delete qTranslatorAddress;
    }

    return loadSuccess;
}

void TranslatorLoader::initFile(QString languageName)
{
    using namespace Const_TranslatorLoader;

    const QString qtPathSplitter = "/";
    const QString translateFileSuffix = ".qm";

    // Qt translate
    // Fail safe, no translation provided in Qt 4.8.7 installation
    loadTranslate("qt", qtPathSplitter, translateFileSuffix, languageName);

    // Prefetch translate
    bool loadSuccess = loadTranslate("prefetch", qtPathSplitter, translateFileSuffix, languageName);

    // Final check, program should end if global init doesn't find any translate file
    if (loadSuccess == false)
    {
        LAST_KNOWN_POSITION(2)
        throw std::runtime_error(Exception::FailedToLoadAnyTranslateFile);
    }
}
