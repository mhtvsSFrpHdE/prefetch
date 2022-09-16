#include <QTextStream>
#include <QMutex>

// Static class
class StdOut
{
public:
    static QTextStream *consoleOutput;

    // Any init code
    static void init();

    // Print
    static void print(QString textToPrint);

    // Print line (append endl after text)
    static void printLine(QString textToPrint);

    // Print endl
    static void printEndl();

    // Without flush printed text may not appear in console immediately
    static void flush();

    // Prevent access stdio at same time
    static QMutex printLock;
    static void lock();
    static void unlock();

private:
    // Disallow creating an instance of this object
    StdOut() {}
};
