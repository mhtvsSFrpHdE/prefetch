#include "sleep.h"
#include "..\core.h"
#include "..\ReadFile\read_file_thread.h"
#include "..\..\Example\semaphore_example.h"

// Sleep prefetch interval, unlock stop mutex after sleep done
void Core_Sleep::sleep()
{
    typedef Core_ReadFileThread crft;
    typedef SemaphoreExample se;

    // Do not run new sleep thread in stop status
    if (se::available(crft::stopSemaphore))
    {
        return;
    }

    Core::sleepThreadAddress->start();
    Core::sleepThreadAddress->wait();
}
