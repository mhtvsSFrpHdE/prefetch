#include <QThread>

class SleepThread : public QThread
{
    Q_OBJECT
public:
    SleepThread();

    unsigned long sleepTimeInSeconds;

    void run();
};