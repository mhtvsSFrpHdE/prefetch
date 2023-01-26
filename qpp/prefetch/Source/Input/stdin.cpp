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

    // Mutex
    freezeMutex = new QMutex();

    Global::inputLoopThreadAddress = new InputLoopThread();
}

void StdIn::start()
{
#if CONSOLE_ENABLED
    Global::inputLoopThreadAddress->start();
#endif
}
