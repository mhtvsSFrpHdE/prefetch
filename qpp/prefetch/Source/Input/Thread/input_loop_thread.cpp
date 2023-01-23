#include "input_loop_thread.h"
#include "receive_text_thread.h"
#include "..\..\Example\self_delete_thread_example.h"
#include "..\..\Input\stdin.h"

// Process input text
void InputLoopThread::receiveText(QString input, void (*callback)())
{
    auto receiveTextThread = new ReceiveTextThread(input, callback);
    auto threadManager = new SlefDeleteThreadExample(receiveTextThread);
    receiveTextThread->start();
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
