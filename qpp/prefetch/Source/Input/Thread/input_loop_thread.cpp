#include "input_loop_thread.h"
#include "..\..\Input\stdin.h"

// Process input text
void InputLoopThread::receiveText(QString input)
{
    // TODO
}

void InputLoopThread::run()
{
    while (true)
    {
        // Get input
        auto input = StdIn::consoleInput->readLine();

        receiveText(input);
    }
}
