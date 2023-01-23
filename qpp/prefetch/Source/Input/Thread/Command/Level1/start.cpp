#include "parent_define.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\Thread\Read\read_thread.h"
#include "..\..\..\..\Core\ReadFile\read_file.h"

void Parent_Prefetch::start()
{
    using namespace Const_Input::Message;

    // Report trying to start
    StdOut::printLine(TryingToStart);

    // Discard rest sleep time if sleep running
    ReadFile::sleepThreadAddress->discard();

    // Not pausing
    if (ReadThread::stop == false)
    {
        return;
    }
    // Pausing
    else
    {
        ReadThread::stop = false;
        ReadThread::stopMutex->unlock();
    }
}
