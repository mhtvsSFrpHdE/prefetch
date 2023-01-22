#include "run_sleep.h"
#include "read_file.h"
#include "..\Thread\Read\read_thread.h"
#include "..\..\Output\log.h"

// Sleep prefetch interval, unlock pause mutex after sleep done
void Run_Sleep::sleep()
{
    // Do not run new sleep thread in pause status
    if (ReadThread::pause)
    {
        return;
    }

    ReadFile::sleepThreadAddress->start();
    ReadFile::sleepThreadAddress->wait();
}
