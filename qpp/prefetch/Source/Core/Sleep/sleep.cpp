#include "sleep.h"
#include "../core.h"
#include "../ReadFile/read_file_thread.h"
#include "../../Example/semaphore_example.h"

// Sleep prefetch interval, unlock stop mutex after sleep done
void Core_Sleep::sleep()
{
    typedef Core_ReadFileThread crft;
    typedef SemaphoreExample se;

    // Do not run new sleep thread in stop status
    bool stopped = se::available(crft::stopSemaphore) == false;
    if (stopped)
    {
        return;
    }

    Core::sleepThreadAddress->start();
    Core::sleepThreadAddress->wait();
}
