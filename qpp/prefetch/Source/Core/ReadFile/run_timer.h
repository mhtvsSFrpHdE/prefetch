#include <QString>

// Wrapper to access QTimer functions
class Run_Timer
{
public:
    static QString timeConsumed(qint64 miliseconds);
};
