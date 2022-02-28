#include <QTranslator>

// Static class
class Translate
{
public:
    // Global QTranslator object, it's a pointer
    static QTranslator *translator;

    // Any init code
    static void init();

private:
    // Disallow creating an instance of this object
    Translate() {}
};
