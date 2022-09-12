#include <QTextStream>
#include <QTimer>

#include "..\..\Global\global.h"
#include "..\..\Input\stdin.h"
#include "..\..\Output\stdout.h"
#include "..\..\Core\Thread\read_thread.h"
#include "..\..\Input\const_input.h"
#include "..\..\Core\start_process.h"

LoopThread::LoopThread() {}

// Process input text
void LoopThread::receiveText(QString input)
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

void LoopThread::run()
{
    while (true)
    {
        // Get input
        auto input = StdIn::consoleInput->readLine();

        receiveText(input);
    }
}

namespace ConsoleCommandFunction_Level1
{
    void pause()
    {
        using namespace Const_Input::Message;
        StdOut::printLine(TryingToPause);

        ReadThread::pause = true;

        StdOut::printLine(PauseRequested);
    };

    void resume()
    {
        using namespace Const_Input::Message;
        StdOut::printLine(TryingToResume);

        ReadThread::pause = false;

        if (ReadFile::sleepThreadAddress->isRunning())
        {
            ReadFile::sleepThreadAddress->terminate();
        }
    }

    void exit()
    {
        using namespace Const_Input::Message;
        StdOut::printLine(TryingToExit1);
        StdOut::printLine(TryingToExit2);

        // Remove MainWindow
        Global::qMainWindow->hide();

        // Remove tray icon
        TrayIcon::stop();

        // Stop QT event loop on main thread
        Global::qGuiApplication->quit();
    }

    void traydc()
    {
        auto mainWindowVisible = Global::qMainWindow->isVisible();
        if (mainWindowVisible)
        {
            Global::qMainWindow->hide();
        }
        else
        {
            // Restore and bring to front
            Global::qMainWindow->show();
            QTimer::singleShot(0, Global::qMainWindow, SLOT(restored_slot()));
        }
    }

    void test()
    {
        using namespace Const_Input::Message;
        StdOut::printLine(Test);
    }
}

namespace ConsoleCommandFunction_Level2
{
    void run(QString command)
    {
        using namespace Const_Input::Message;

        StdOut::printLine(TryingToRun1);
        StdOut::printLine(TryingToRun2 + command);

        StartProcess::startProcess(command);
    }
}

using namespace Const_Input;
// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, void (*)()> LoopThread::commandMap_level1(
    std::map<QString, void (*)()>{
        {Command_Level1::pause, &ConsoleCommandFunction_Level1::pause},
        {Command_Level1::resume, &ConsoleCommandFunction_Level1::resume},
        {Command_Level1::test, &ConsoleCommandFunction_Level1::test},
        {Command_Level1::exit, &ConsoleCommandFunction_Level1::exit},
        {Command_Level1::traydc, &ConsoleCommandFunction_Level1::traydc}});
QMap<QString, void (*)(QString)> LoopThread::commandMap_level2(
    std::map<QString, void (*)(QString)>{
        {Command_Level2::run, &ConsoleCommandFunction_Level2::run}});
