#include <QTranslator>

// Qt translator init
class TranslatorLoader
{
public:
    static QList<QTranslator *> installedTranslator;

    // Determine which translate file to be used
    static void initFile();
    // Read message from translate file
    static void initMessage();
};
