#include <QTextStream>

#include "loop_thread.h"
#include "..\..\Input\stdin.h"
#include "..\..\Output\stdout.h"

LoopThread::LoopThread() {}

void LoopThread::run()
{
    while (true)
    {
        // Get input
        auto input = StdIn::consoleInput->readLine();

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
}

namespace ConsoleCommandFunction
{
    void pause()
    {
        *StdOut::consoleOutput << "Trying to pause prefetch"
                               << endl;
        StdOut::consoleOutput->flush();
    };
}

// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, void (*)()> LoopThread::commandMap(
    std::map<QString, void (*)()>{
        {"pause", &ConsoleCommandFunction::pause}});
