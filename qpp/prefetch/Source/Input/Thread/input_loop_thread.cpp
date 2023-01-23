#include "input_loop_thread.h"
#include "receive_text_thread.h"
#include "..\..\Input\stdin.h"

// Process input text
void InputLoopThread::receiveText(QString input, void (*callback)())
{
    auto backgroundWorker = new ReceiveTextThread(input, callback);
    backgroundWorker->start();
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
