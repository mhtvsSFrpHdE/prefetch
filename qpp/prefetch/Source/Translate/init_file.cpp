#include <QLibraryInfo>
#include <QLocale>
#include <QStringList>

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

// prefetch_en_US.qm
// prefetch_zh_CN.qm
QString loadTranslate_load_getTranslateFile(QString translateName, QString language, QString translateFileSuffix)
{
    return translateName + "_" + language + translateFileSuffix;
}

// prefetch_en_US.qm
// prefetch_zh_CN.qm
QString loadTranslate_load_getTranslateFile(QString translateName, QString translateFileSuffix)
{
    return loadTranslate_load_getTranslateFile(translateName, QLocale::system().name(), translateFileSuffix);
}

// Load translate file, install if success
bool loadTranslate_load(
    QTranslator *translator,
    QString translateName,
    QString translateFolder,
    QString translateFileSuffix)
{
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Instance_ConfigKeyName;
    using namespace Const_Setting;

    // Get language from setting
    QString getSettingLanguage;
    getSettingLanguage = Setting::getString(Instance, Language, Setting::setting);
    if (getSettingLanguage == Instance_Language_Value::Default)
    {
        getSettingLanguage = loadTranslate_load_getTranslateFile(translateName, translateFileSuffix);
    }
    else
    {
        getSettingLanguage = loadTranslate_load_getTranslateFile(translateName, getSettingLanguage, translateFileSuffix);
    }

    // Confirm translate exist
    bool translateNotFound = true;

    // Try install setting language
    {
        bool installResult = loadTranslate_load_tryInstall(translator, getSettingLanguage, translateFolder);
        if (installResult)
        {
            translateNotFound = false;
        }
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

bool loadTranslate(QString translateName, QString qtPathSplitter, QString translateFileSuffix)
{
    // Keep translator in memory
    // https://stackoverflow.com/questions/28509106/translation-not-working-in-qt
    auto qTranslatorAddress = new QTranslator();

    auto translateFolder = loadTranslate_getTranslateFolder(qtPathSplitter, translateName);

    // Get load result
    bool loadSuccess = loadTranslate_load(qTranslatorAddress, translateName, translateFolder, translateFileSuffix);
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

void TranslatorLoader::initFile()
{
    const QString qtPathSplitter = "/";
    const QString translateFileSuffix = ".qm";

    // Qt translate
    // Fail safe, no translation provided in Qt 4.8.7 installation
    loadTranslate("qt", qtPathSplitter, translateFileSuffix);

    // Prefetch translate
    bool loadSuccess = loadTranslate("prefetch", qtPathSplitter, translateFileSuffix);
    if (loadSuccess == false)
    {
        throw;
    }
}
