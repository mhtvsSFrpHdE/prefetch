#include "parent_define.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\ReadFile\read_file_thread.h"
#include "..\..\..\..\Core\core.h"

void Parent_Prefetch::start()
{
    using namespace Const_Input::Message;

    // Report trying to start
    StdOut::printLine(TryingToStart);

    // Discard rest sleep time if sleep running
    Core::sleepThreadAddress->discard();

    // Not pausing
    if (Core_ReadFileThread::stop == false)
    {
        return;
    }
    // Pausing
    else
    {
        Core_ReadFileThread::stop = false;
        Core_ReadFileThread::stopMutex->unlock();
    }
}
