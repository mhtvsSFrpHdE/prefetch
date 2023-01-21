#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\Thread\Read\read_thread_crtrt.h"
#include "..\..\..\..\Core\ReadFile\read_file.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::resume()
{
    using namespace Const_Input::Message;

    // Report trying to resume
    StdOut::printLine(TryingToResume);

    // Discard rest sleep time if sleep running
    ReadFile::sleepThreadAddress->discard();

    // Not pausing
    if (ReadThread::pause == false)
    {
        return;
    }
    // Pausing
    else
    {
        ReadThread::pause = false;
        ReadThread::pauseMutex->unlock();
    }
}
