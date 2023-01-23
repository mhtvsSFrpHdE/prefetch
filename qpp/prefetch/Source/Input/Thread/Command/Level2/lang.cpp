#include <QTranslator>

#include "parent_define.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Define\define.h"
#include "..\..\..\..\Translate\translator_loader.h"
#include "..\..\..\..\Global\global.h"
#include "..\..\..\..\Global\const_global.h"
#include "..\..\..\..\Translate\translate_tool.h"
#include "..\..\..\..\Output\log.h"

void Parent_Prefetch::lang(QString command)
{
    LAST_KNOWN_POSITION(0)

    using namespace Const_Input::Message;
    using namespace Const_Global::CommonString;

#if TRANSLATE_ENABLED
    StdOut::printLine(TryingToLoadTranslate + command);

    LAST_KNOWN_POSITION(3)
    TranslateTool::lock();

    // Backup exist translator address
    QList<QTranslator *> installedTranslatorBackup;
    installedTranslatorBackup.append(TranslatorLoader::installedTranslator);
    TranslatorLoader::installedTranslator.clear();

    // Load new translator
    try
    {
        TranslatorLoader::initFile(command);
    }
    catch (...)
    {
        // Ignore exception
    }

    // Check load result
    bool hasTranslator = TranslatorLoader::installedTranslator.count() > 0;
    if (hasTranslator)
    {
        // Delete obsolute translator
        for (int i = 0; i < installedTranslatorBackup.count(); ++i)
        {
            auto translator = installedTranslatorBackup[i];
            Global::qGuiApplication->removeTranslator(translator);
            delete translator;
        }

        // Update text
        TranslatorLoader::initMessage();

        // Report back to GUI
        StdOut::printLine(Tab + TranslateFileLoaded + command);
    }
    else
    {
        // Restore exist translator address
        TranslatorLoader::installedTranslator.append(installedTranslatorBackup);

        // Report back to GUI
        StdOut::printLine(Tab + FailedToLoadTranslate + command);
    }

    TranslateTool::unlock();
    LAST_KNOWN_POSITION(4)
#else
    StdOut::printLine(TranslateNotAvailable);
#endif

    LAST_KNOWN_POSITION(1)
}
