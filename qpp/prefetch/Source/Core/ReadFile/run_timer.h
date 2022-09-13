#include <QString>

// Wrapper to access QTimer functions
class Run_Timer
{
public:
    static QString timeConsumed(qint64 miliseconds);

private:
    // Disallow creating an instance of this object
    Run_Timer();
};
