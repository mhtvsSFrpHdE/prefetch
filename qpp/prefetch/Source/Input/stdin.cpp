#include "stdin.h"

#include "../Global/global.h"
#include "../Example/semaphore_example.h"

#if CONSOLE_ENABLED
QTextStream *StdIn::consoleInput;
#endif

void StdIn::init()
{
#if CONSOLE_ENABLED
    consoleInput = new QTextStream(stdin);
#endif

    // Mutex
    freezeSemaphore = SemaphoreExample::getMutex();

    Global::inputLoopThreadAddress = new InputLoopThread();
}

void StdIn::start()
{
#if CONSOLE_ENABLED
    Global::inputLoopThreadAddress->start();
#endif
}

void StdInExample::restore_ordinary()
{
    Global::runOnUiThreadAddress->run(&StdIn::restore);
}
