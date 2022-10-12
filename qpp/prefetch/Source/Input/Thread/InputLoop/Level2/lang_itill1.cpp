#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level2

void Parent::lang(QString command)
{
    using namespace Const_Input::Message;

    StdOut::printLine(TryingToLoadTranslate + command);

    // TODO:
}
