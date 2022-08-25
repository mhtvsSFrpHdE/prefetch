#include <QTextStream>

#include "..\..\Global\global.h"
#include "..\..\Input\stdin.h"
#include "..\..\Output\stdout.h"
#include "..\..\Core\Thread\read_thread.h"

LoopThread::LoopThread() {}

// Process input text
void LoopThread::receiveText(QString input)
{
    // Find command and run command
    if (commandMap.contains(input))
    {
        auto target = commandMap[input];
        (*target)();
    }
    // Command not found
    else
    {
        *StdOut::consoleOutput << "Invalid command"
                               << endl;
        StdOut::consoleOutput->flush();
    }
}

void LoopThread::run()
{
    while (true)
    {
        // Get input
        auto input = StdIn::consoleInput->readLine();

        receiveText(input);
    }
}

namespace ConsoleCommandFunction
{
    void pause()
    {
        *StdOut::consoleOutput << "Trying to pause prefetch"
                               << endl;
        StdOut::consoleOutput->flush();

        ReadThread::pause = true;

        *StdOut::consoleOutput << "Pause has requested, good luck"
                               << endl;
        StdOut::consoleOutput->flush();
    };

    void resume()
    {
        *StdOut::consoleOutput << "Trying to resume prefetch"
                               << endl;
        StdOut::consoleOutput->flush();

        ReadThread::pause = false;

        if (ReadFile::sleepThreadAddress->isRunning())
        {
            ReadFile::sleepThreadAddress->terminate();
        }
    }

    void test()
    {
        *StdOut::consoleOutput << "This function contain test code"
                               << endl;
        StdOut::consoleOutput->flush();
    }
}

// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, void (*)()> LoopThread::commandMap(
    std::map<QString, void (*)()>{
        {"pause", &ConsoleCommandFunction::pause},
        {"resume", &ConsoleCommandFunction::resume},
        {"test", &ConsoleCommandFunction::test}});
