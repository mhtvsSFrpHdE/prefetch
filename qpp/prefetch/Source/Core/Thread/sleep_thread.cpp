#include "sleep_thread.h"

SleepThread::SleepThread()
{
    SleepThread::sleepTimeInSeconds = sleepTimeInSeconds;
}

void SleepThread::run()
{
    sleep(sleepTimeInSeconds);
}
