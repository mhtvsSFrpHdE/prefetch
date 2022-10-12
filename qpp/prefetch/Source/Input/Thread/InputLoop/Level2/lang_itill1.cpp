#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Define\define.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level2

void Parent::lang(QString command)
{
    // TODO:
    using namespace Const_Input::Message;

#if TRANSLATE_ENABLED
    StdOut::printLine(TryingToLoadTranslate + command);
#else
    StdOut::printLine(TranslateNotAvailable);
#endif
}
