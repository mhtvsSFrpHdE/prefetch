#include "parent_define.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\ReadFile\read_file_thread.h"
#include "..\..\..\..\Output\log.h"

void Parent_Prefetch::stop()
{
    using namespace Const_Input::Message;

    // Report trying to stop
    StdOut::printLine(TryingToStop);

    // Check stop status
    if (Core_ReadFileThread::stop)
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
    Core_ReadFileThread::stopMutex->lock();

    // Set stop status, thread pool will skip run
    Core_ReadFileThread::stop = true;

    // Report stop success
    StdOut::printLine(StopRequested);

    // End execute
    return;
};
