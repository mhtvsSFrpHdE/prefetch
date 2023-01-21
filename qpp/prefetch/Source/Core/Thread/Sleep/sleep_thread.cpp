#include "sleep_thread.h"

void SleepThread::run()
{
    sleep(sleepTimeInSeconds);

    if (callback != NULL)
    {
        (*callback)();
    }
}

void SleepThread::discard()
{
    if (isRunning())
    {
        terminate();
    }
}
