#include <QTextStream>
#include <QTimer>

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
        StdOut::printLine("Invalid command");
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
        StdOut::printLine("Trying to pause prefetch");

        ReadThread::pause = true;

        StdOut::printLine("Pause has requested, good luck");
    };

    void resume()
    {
        StdOut::printLine("Trying to resume prefetch");

        ReadThread::pause = false;

        if (ReadFile::sleepThreadAddress->isRunning())
        {
            ReadFile::sleepThreadAddress->terminate();
        }
    }

    void exit()
    {
        StdOut::printLine("Trying to exit prefetch");
        StdOut::printLine("    This can take a while in some case");

        // Free thread pool
        // If exit QT before thread pool done
        //     the program won't exit correctly after main return 0
        //     just like a dead loop in somewhere

        // Prevent another round prefetch being started
        Global::readFileLoopThreadAddress->terminate();

        // Tell running task to stop
        pause();

        // Wait thread pool to response
        ReadFile::readThreadPool->waitForDone();

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
        StdOut::printLine("This function contain test code");
    }
}

// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, void (*)()> LoopThread::commandMap(
    std::map<QString, void (*)()>{
        {"pause", &ConsoleCommandFunction::pause},
        {"resume", &ConsoleCommandFunction::resume},
        {"test", &ConsoleCommandFunction::test},
        {"exit", &ConsoleCommandFunction::exit},
        {"traydc", &ConsoleCommandFunction::traydc}});
