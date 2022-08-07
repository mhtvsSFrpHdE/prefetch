#include "stdin.h"

LoopThread *StdIn::loopThreadAddress = NULL;

void StdIn::init()
{
    loopThreadAddress = new LoopThread();
}

void StdIn::start()
{
    loopThreadAddress->start();
}
