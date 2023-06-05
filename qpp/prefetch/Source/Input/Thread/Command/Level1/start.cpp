#include "parent_define.h"
#include "../../../../Input/const_input.h"
#include "../../../../Output/stdout.h"
#include "../../../../ReadLoop/ReadFile/read_file_thread.h"
#include "../../../../ReadLoop/read_loop.h"
#include "../../../../Example/semaphore_example.h"

void Parent_Prefetch::start()
{
    using namespace Const_Input::Message;

    typedef ReadLoop_ReadFileThread crft;
    typedef SemaphoreExample se;

    // Report trying to start
    StdOut::printLine(TryingToStart);

    // Discard rest sleep time if sleep running
    ReadLoop::sleepThreadAddress->discard();

    // Not pausing
    if (ReadLoop_ReadFileThread::stop == false)
    {
        return;
    }
    // Pausing
    else
    {
        ReadLoop_ReadFileThread::stop = false;
        se::unlock(crft::stopSemaphore);
    }
}
