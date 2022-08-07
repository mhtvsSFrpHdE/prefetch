#include "stdin.h"

#include "..\Global\global.h"

QTextStream *StdIn::consoleInput;

void StdIn::init()
{
    consoleInput = new QTextStream(stdin);
    Global::inputLoopThreadAddress = new LoopThread();
}

void StdIn::start()
{
    Global::inputLoopThreadAddress->start();
}
