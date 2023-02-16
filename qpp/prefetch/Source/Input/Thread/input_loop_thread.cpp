#include "input_loop_thread.h"
#include "receive_text_thread.h"
#include "..\..\Example\self_delete_thread_example.h"
#include "..\..\Example\semaphore_example.h"
#include "..\..\Define\define.h"
#include "..\..\Input\stdin.h"
#include "..\..\Output\log.h"
#include "..\..\Global\global.h"

// Process input text
// Non blocking
void InputLoopThread::receiveText_threaded(QString input, void (*callback)())
{
    auto receiveTextThread = new ReceiveTextThread(input, callback);
    auto threadManager = new SlefDeleteThreadExample(receiveTextThread);
    receiveTextThread->start();
}

void InputLoopThread::receiveText_block(QString input, void (*callback)())
{
    auto receiveTextThread = new ReceiveTextThread(input, callback);

    receiveTextThread->start();
    receiveTextThread->wait();
    delete receiveTextThread;
}

void InputLoopThread::run()
{
#if CONSOLE_ENABLED
    while (true)
    {
        // Get input
        // Block until Enter pressed
        auto input = StdIn::consoleInput->readLine();

        // Lock mutex
        LAST_KNOWN_POSITION(3)
        bool locked = SemaphoreExample::tryLock(StdIn::freezeSemaphore);
        if (locked == false)
        {
            // Ignore request
            continue;
        }

        Global::runOnUiThreadAddress->run_block(&StdIn::freeze);

        receiveText_threaded(input, &StdInExample::restore_ordinary);
    }
#endif
}
