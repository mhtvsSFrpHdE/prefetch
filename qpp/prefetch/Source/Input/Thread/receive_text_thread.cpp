#include "receive_text_thread.h"
#include "..\..\Input\const_input.h"
#include "..\..\Output\stdout.h"

void ReceiveTextThread::run_callback()
{
    if (callback == NULL)
    {
        return;
    }

    (*callback)();
}

void ReceiveTextThread::run()
{
    // Find level 1 command
    // Assume input is "stop"
    {
        if (commandMap_level1.contains(input))
        {
            // Run command
            auto target = commandMap_level1[input];
            (*target)();

            run_callback();
            return;
        }
    }

    // Find level 2 command
    // Assume input is "run explorer Firefox.lnk"
    {
        using namespace Const_Input::Command_Level2;

        // Get "run" part and sumbit to command map
        auto commandPart = input.section(splitter, 0, 0);
        if (commandMap_level2.contains(commandPart))
        {
            // Get "explorer Firefox.lnk" part and sumbit to target function
            auto parameterPart = input.section(splitter, 1);

            auto target = commandMap_level2[commandPart];
            (*target)(parameterPart);

            run_callback();
            return;
        }
    }

    // No match, invalid command
    using namespace Const_Input::Message;
    StdOut::printLine(InvalidCommand);
    run_callback();
    return;
}

ReceiveTextThread::ReceiveTextThread(QString input, void (*callback)())
{
    ReceiveTextThread::input = input;
    ReceiveTextThread::callback = callback;
}

using namespace Const_Input;
// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, void (*)()> ReceiveTextThread::commandMap_level1(
    std::map<QString, void (*)()>{
        {Command_Level1::stop, &ConsoleCommandFunction_Level1::stop},
        {Command_Level1::start, &ConsoleCommandFunction_Level1::start},
        {Command_Level1::test, &ConsoleCommandFunction_Level1::test},
        {Command_Level1::exit, &ConsoleCommandFunction_Level1::exit},
        {Command_Level1::traydc, &ConsoleCommandFunction_Level1::traydc},
        {Command_Level1::expiresc, &ConsoleCommandFunction_Level1::expiresc}});
QMap<QString, void (*)(QString)> ReceiveTextThread::commandMap_level2(
    std::map<QString, void (*)(QString)>{
        {Command_Level2::run, &ConsoleCommandFunction_Level2::run},
        {Command_Level2::run_quiet, &ConsoleCommandFunction_Level2::run_quiet},
        {Command_Level2::lang, &ConsoleCommandFunction_Level2::lang}});
