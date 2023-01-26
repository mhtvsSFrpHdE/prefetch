#include "stdin.h"

#include "..\Global\global.h"

#if CONSOLE_ENABLED
QTextStream *StdIn::consoleInput;
#endif

void StdIn::init()
{
#if CONSOLE_ENABLED
    consoleInput = new QTextStream(stdin);
#endif

    Global::inputLoopThreadAddress = new InputLoopThread();
}

void StdIn::start()
{
#if CONSOLE_ENABLED
    Global::inputLoopThreadAddress->start();
#endif
}
