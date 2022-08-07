#include "sleep_thread.h"

SleepThread::SleepThread(unsigned long sleepTimeInSeconds)
{
    SleepThread::sleepTimeInSeconds = sleepTimeInSeconds;
}

void SleepThread::run()
{
    sleep(sleepTimeInSeconds);
}