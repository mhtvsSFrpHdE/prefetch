#include "sleep.h"
#include "..\core.h"
#include "..\ReadFile\read_file_thread.h"
#include "..\..\Output\log.h"

// Sleep prefetch interval, unlock stop mutex after sleep done
void Core_Sleep::sleep()
{
    // Do not run new sleep thread in stop status
    // TODO: QMutex tryLock?
    if (Core_ReadFileThread::stop)
    {
        return;
    }

    Core::sleepThreadAddress->start();
    Core::sleepThreadAddress->wait();
}
