#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\Thread\read_thread.h"
#include "..\..\..\..\Core\ReadFile\read_file.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::resume()
{
    using namespace Const_Input::Message;
    StdOut::printLine(TryingToResume);

    ReadThread::pause = false;

    if (ReadFile::sleepThreadAddress->isRunning())
    {
        ReadFile::sleepThreadAddress->terminate();
    }
}
