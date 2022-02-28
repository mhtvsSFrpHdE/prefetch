#include <QCoreApplication>

// Static class
class Global
{
public:
    // Global QCoreApplication object, it's a pointer
    static QCoreApplication *qCoreApplication;

    // Any init code
    static void init();

private:
    // Disallow creating an instance of this object
    Global() {}
};
