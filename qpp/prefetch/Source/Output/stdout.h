#include <QTextStream>

// Static class
class StdOut
{
public:
    // Global QTextStream object, it's a pointer
    static QTextStream *consoleOutput;

    // Any init code
    static void init();

private:
    // Disallow creating an instance of this object
    StdOut() {}
};
