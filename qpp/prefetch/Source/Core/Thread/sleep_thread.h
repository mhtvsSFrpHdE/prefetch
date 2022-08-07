#include <QThread>

class SleepThread : public QThread
{
public:
    SleepThread(unsigned long sleepTimeInMilliseconds);

    unsigned long sleepTimeInSeconds;

    void run();
};