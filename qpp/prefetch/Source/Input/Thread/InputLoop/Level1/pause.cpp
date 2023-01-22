#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\Thread\Read\read_thread.h"
#include "..\..\..\..\Output\log.h"
#include "..\..\..\..\Core\ReadFile\read_file.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::pause()
{
    using namespace Const_Input::Message;

    // Report trying to pause
    StdOut::printLine(TryingToPause);

    // Check pause status
    if (ReadThread::pause)
    {
        // Report pause success
        StdOut::printLine(PauseRequested);

        // End execute
        return;
    }

    // Lock pause mutex
    //
    // Once locked, read loop will be blocked at check point
    LAST_KNOWN_POSITION(3)
    ReadThread::pauseMutex->lock();

    // Set pause status, thread pool will skip run
    ReadThread::pause = true;

    // Report pause success
    StdOut::printLine(PauseRequested);

    // End execute
    return;
};
