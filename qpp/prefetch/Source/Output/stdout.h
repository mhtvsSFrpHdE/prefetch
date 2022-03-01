#include <QTextStream>

// Static class
class StdOut
{
public:
    static QTextStream *consoleOutput;

    // Any init code
    static void init();

private:
    // Disallow creating an instance of this object
    StdOut() {}
};
