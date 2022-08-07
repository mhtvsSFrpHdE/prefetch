#include "loop_thread.h"
#include "..\..\Output\stdout.h"

LoopThread::LoopThread() {}

void LoopThread::run()
{
    while (true)
    {
        *StdOut::consoleOutput << "Std in loop thread test"
                               << endl;
        StdOut::consoleOutput->flush();

        sleep(3);
    }
}
