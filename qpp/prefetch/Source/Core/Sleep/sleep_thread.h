#include <QThread>

// Use thread to sleep, so terminate running sleep is possible
class SleepThread : public QThread
{
    Q_OBJECT
public:
    unsigned long sleepTimeInSeconds = 0;
    void (*callback)() = NULL;

    void run();

    // If running, terminate
    void discard();
};
