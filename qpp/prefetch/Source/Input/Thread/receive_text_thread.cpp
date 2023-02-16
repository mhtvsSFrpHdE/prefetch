#include <QStringList>

#include "receive_text_thread.h"
#include "..\..\Input\const_input.h"
#include "..\..\Output\stdout.h"
#include "..\..\Global\const_global.h"

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
    using namespace Const_Global::CommonString;

    // Parse input string list
    auto inputStringList = rawInput.split(NewLine);
    bool inputHandled = false;

    // Consume input string list
    for (int i = 0; i < inputStringList.size(); ++i)
    {
        // Get individual input
        auto input = inputStringList[i];

        // Find level 1 command
        // Assume input is "stop"
        {
            if (commandMap_level1.contains(input))
            {
                // Run command
                auto target = commandMap_level1[input];
                (*target)();

                inputHandled = true;
                continue;
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

                inputHandled = true;
                continue;
            }
        }
    }

    // No match, report invalid command
    if (inputHandled == false)
    {
        StdOut::printLine(Const_Input::Message::InvalidCommand);
    }

    // End input
    run_callback();
    return;
}

ReceiveTextThread::ReceiveTextThread(QString input, void (*callback)())
{
    ReceiveTextThread::rawInput = input;
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
        {Command_Level1::expiresc, &ConsoleCommandFunction_Level1::expiresc},
        {Command_Level1::startup, &ConsoleCommandFunction_Level1::startup}});
QMap<QString, void (*)(QString)> ReceiveTextThread::commandMap_level2(
    std::map<QString, void (*)(QString)>{
        {Command_Level2::run, &ConsoleCommandFunction_Level2::run},
        {Command_Level2::run_quiet, &ConsoleCommandFunction_Level2::run_quiet},
        {Command_Level2::lang, &ConsoleCommandFunction_Level2::lang}});
