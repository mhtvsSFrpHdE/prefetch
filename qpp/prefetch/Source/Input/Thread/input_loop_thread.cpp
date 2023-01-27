#include "input_loop_thread.h"
#include "receive_text_thread.h"
#include "..\..\Example\self_delete_thread_example.h"
#include "..\..\Define\define.h"
#include "..\..\Input\stdin.h"
#include "..\..\Output\log.h"
#include "..\..\Global\global.h"

// Process input text
// Non blocking
void InputLoopThread::receiveText(QString input, void (*callback)())
{
    auto receiveTextThread = new ReceiveTextThread(input, callback);
    auto threadManager = new SlefDeleteThreadExample(receiveTextThread);
    receiveTextThread->start();
}

#if CONSOLE_ENABLED
// Run stdin_restore on ui thread
void run_callback_toOrdinary()
{
    Global::runOnUiThreadAddress->run(&StdIn::restore);
}
#endif

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
        bool locked = StdIn::freezeMutex->tryLock();
        if (locked == false)
        {
            // Ignore request without hint right now
            // TODO
            continue;
        }

        Global::runOnUiThreadAddress->run_block(&StdIn::freeze);

        receiveText(input, &run_callback_toOrdinary);
    }
#endif
}
