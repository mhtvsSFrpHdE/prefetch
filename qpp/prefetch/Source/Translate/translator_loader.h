#include <QTranslator>

// Qt translator init
class TranslatorLoader
{
public:
    static QList<QTranslator *> installedTranslator;

    // stdexcept
    //
    // Determine which translate file to be used
    //
    // languageName
    //     When run init, NULL
    //     When run from command, pass command argument
    static void initFile(QString languageName = NULL);
    // Read message from translate file
    static void initMessage();
};
