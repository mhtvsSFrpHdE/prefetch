#include "stdin.h"

#include "..\Global\global.h"
#include "..\Define\define.h"

QTextStream *StdIn::consoleInput;

void StdIn::init()
{
#if CONSOLE_ENABLED == 1
    consoleInput = new QTextStream(stdin);
#endif

    Global::inputLoopThreadAddress = new LoopThread();
}

void StdIn::start()
{
#if CONSOLE_ENABLED == 1
    Global::inputLoopThreadAddress->start();
#endif
}
