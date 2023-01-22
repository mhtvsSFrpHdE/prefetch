#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\Thread\Read\read_thread.h"
#include "..\..\..\..\Output\log.h"
#include "..\..\..\..\Core\ReadFile\read_file.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::stop()
{
    using namespace Const_Input::Message;

    // Report trying to stop
    StdOut::printLine(TryingToStop);

    // Check stop status
    if (ReadThread::stop)
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
    ReadThread::stopMutex->lock();

    // Set stop status, thread pool will skip run
    ReadThread::stop = true;

    // Report stop success
    StdOut::printLine(StopRequested);

    // End execute
    return;
};
