#include <QTranslator>

// Qt translator init
// This class should only use once
class TranslatorLoader
{
public:
    static QList<QTranslator *> installedTranslator;

    // Determine which translate file to be used
    static void initFile();
    // Read message from translate file
    static void initMessage();

private:
    // Disallow creating an instance of this object
    TranslatorLoader() {}
};
