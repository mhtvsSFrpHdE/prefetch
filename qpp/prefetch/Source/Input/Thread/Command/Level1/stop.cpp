#include "parent_define.h"
#include "../../../../Input/const_input.h"
#include "../../../../Output/stdout.h"
#include "../../../../ReadLoop/ReadFile/read_file_thread.h"
#include "../../../../Output/log.h"
#include "../../../../Example/semaphore_example.h"

void Parent_Prefetch::stop()
{
    using namespace Const_Input::Message;

    typedef ReadLoop_ReadFileThread crft;
    typedef SemaphoreExample se;

    // Report trying to stop
    StdOut::printLine(TryingToStop);

    // Check stop status
    if (ReadLoop_ReadFileThread::stop)
    {
        // Report stop success
        StdOut::printLine(StopRequested);

        // End execute
        return;
    }

    // Lock stop mutex
    //
    // Once locked, read loop will be blocked at check point
    LAST_KNOWN_POSITION(3)
    se::lock(crft::stopSemaphore);

    // Set stop status, thread pool will skip run
    ReadLoop_ReadFileThread::stop = true;

    // Report stop success
    StdOut::printLine(StopRequested);

    // End execute
    return;
};
