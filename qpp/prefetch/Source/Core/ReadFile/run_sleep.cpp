#include "run_sleep.h"
#include "read_file.h"

void Run_Sleep::sleep(unsigned long secs)
{
    ReadFile::sleepThreadAddress->sleepTimeInSeconds = secs;

    ReadFile::sleepThreadAddress->start();
    ReadFile::sleepThreadAddress->wait();
}
