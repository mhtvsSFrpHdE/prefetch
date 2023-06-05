#include "sleep.h"
#include "../read_loop.h"
#include "../ReadFile/read_file_thread.h"
#include "../../Example/semaphore_example.h"

// Sleep prefetch interval, unlock stop mutex after sleep done
void ReadLoop_Sleep::sleep()
{
    typedef ReadLoop_ReadFileThread crft;
    typedef SemaphoreExample se;

    // Do not run new sleep thread in stop status
    bool stopped = se::available(crft::stopSemaphore) == false;
    if (stopped)
    {
        return;
    }

    ReadLoop::sleepThreadAddress->start();
    ReadLoop::sleepThreadAddress->wait();
}
