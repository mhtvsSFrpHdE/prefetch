#include "input_loop_thread.h"
#include "..\..\Input\const_input.h"
#include "..\..\Output\stdout.h"
#include "..\..\Input\stdin.h"

InputLoopThread::InputLoopThread() {}

// Process input text
void InputLoopThread::receiveText(QString input)
{
    // Find level 1 command and run command
    if (commandMap_level1.contains(input))
    {
        auto target = commandMap_level1[input];
        (*target)();

        return;
    }

    // Find level 2
    {
        // Assume input is "run explorer Firefox.lnk"

        using namespace Const_Input::Command_Level2;

        // Get "run" part and sumbit to command map
        auto commandPart = input.section(splitter, 0, 0);
        if (commandMap_level2.contains(commandPart))
        {
            // Get "explorer Firefox.lnk" part and sumbit to target function
            auto parameterPart = input.section(splitter, 1);

            auto target = commandMap_level2[commandPart];
            (*target)(parameterPart);

            return;
        }
    }

    // No match, invalid command
    using namespace Const_Input::Message;
    StdOut::printLine(InvalidCommand);
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

using namespace Const_Input;
// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, void (*)()> InputLoopThread::commandMap_level1(
    std::map<QString, void (*)()>{
        {Command_Level1::pause, &ConsoleCommandFunction_Level1::pause},
        {Command_Level1::resume, &ConsoleCommandFunction_Level1::resume},
        {Command_Level1::test, &ConsoleCommandFunction_Level1::test},
        {Command_Level1::exit, &ConsoleCommandFunction_Level1::exit},
        {Command_Level1::traydc, &ConsoleCommandFunction_Level1::traydc},
        {Command_Level1::expiresc, &ConsoleCommandFunction_Level1::expiresc}});
QMap<QString, void (*)(QString)> InputLoopThread::commandMap_level2(
    std::map<QString, void (*)(QString)>{
        {Command_Level2::run, &ConsoleCommandFunction_Level2::run},
        {Command_Level2::run_quiet, &ConsoleCommandFunction_Level2::run_quiet},
        {Command_Level2::lang, &ConsoleCommandFunction_Level2::lang}});
