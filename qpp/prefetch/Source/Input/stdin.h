#include <QTextStream>

class StdIn
{
public:
    static QTextStream *consoleInput;

    // Any init code
    static void init();

    // Start read loop
    // This method is NOT blocking
    static void start();
};
