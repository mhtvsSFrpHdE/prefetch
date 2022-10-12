#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::test()
{
    using namespace Const_Input::Message;
    StdOut::printLine(Test);
}
