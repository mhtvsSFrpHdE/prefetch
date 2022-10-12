#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\Thread\read_thread.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::pause()
{
    using namespace Const_Input::Message;
    StdOut::printLine(TryingToPause);

    ReadThread::pause = true;

    StdOut::printLine(PauseRequested);
};
