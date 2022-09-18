#include <QTextStream>
#include <QTimer>

#include "..\..\Global\global.h"
#include "..\..\Global\const_global.h"
#include "..\..\Input\stdin.h"
#include "..\..\Output\stdout.h"
#include "..\..\Core\Thread\read_thread.h"
#include "..\..\Core\const_core.h"
#include "..\..\Input\const_input.h"
#include "..\..\Core\start_process.h"
#include "..\..\Core\scan_cache.h"
#include "..\..\Setting\setting.h"

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

    void exit_quiet()
    {
        // Remove MainWindow
        Global::qMainWindow->hide();

        // Remove tray icon
        TrayIcon::stop();

        // Stop QT event loop on main thread
        Global::qGuiApplication->quit();
    }

    void exit()
    {
        using namespace Const_Input::Message;
        StdOut::printLine(TryingToExit1);
        StdOut::printLine(TryingToExit2);

        exit_quiet();
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

    void expiresc()
    {
        using namespace Const_Input;
        using namespace Const_Input::Message;
        using namespace Const_Global::CommonString;
        using namespace Const_Core::Arg;

        StdOut::printLine(TryingToExpireScanCache);

        if (ScanCache::cacheFileExist == false)
        {
            StdOut::printLine(ScanCacheNotFound);
            return;
        }

        // Shutdown stdio
        StdOut::shutdown();

        // Stop running thread
        pause();
        ReadFile::readThreadPool->waitForDone();

        // Delete cache file
        QFile::remove(ScanCache::cacheFilePath);

        // Open self again

        // Get exist argument
        //     <.exe> <.ini> <other flag>
        auto selfArgumentsStringList = Global::qGuiApplication->arguments();

        // Get exe
        //     <.exe>
        auto selfExePath = QFileInfo(selfArgumentsStringList[0]).absoluteFilePath();

        // Add exe quote if not already
        //     "<.exe>"
        bool quotedSelfExePath = selfExePath.startsWith(Quote);
        if (!quotedSelfExePath)
        {
            selfExePath = Quote + selfExePath + Quote;
        }

        // Get ini
        //     <.ini>
        // Remove quote if exist
        auto settingFileName = QFileInfo(Setting::settingFilePath).fileName();
        settingFileName.replace(Quote, EmptyString);

        // Collect search result
        bool settingFileNotInArgv = true;
        bool skipStartupNotInArgv = true;
        bool showMainWindowNotInArgv = true;
        // Search start from 2nd element
        QListIterator<QString> iterator(selfArgumentsStringList);
        iterator.next();
        while (iterator.hasNext())
        {
            auto value = iterator.next();

            // Confirm <.ini>
            if (value.contains(settingFileName))
            {

                settingFileNotInArgv = false;
            }

            // Confirm <other flag>
            if (value == SkipStartup)
            {
                skipStartupNotInArgv = false;
            }
            if (value == ShowMainWindow)
            {
                showMainWindowNotInArgv = false;
            }
        }

        // Add necessary arguments if not exist
        if (settingFileNotInArgv)
        {
            // "<.ini>"
            auto settingFilePath_arguments = Quote + settingFileName + Quote;
            selfArgumentsStringList.insert(IniArgi, settingFilePath_arguments);
        }
        if (skipStartupNotInArgv)
        {
            // <other flag>
            selfArgumentsStringList.append(SkipStartup);
        }
        if (showMainWindowNotInArgv)
        {
            selfArgumentsStringList.append(ShowMainWindow);
        }

        // Remove <.exe>
        // Join rest element
        selfArgumentsStringList.removeFirst();

        // Send run quiet command
        //     `run `
        //   + `"<.exe>"`
        //   + `"<.ini>" <other flag>`
        auto self_command = Command_Level2::run_withSplitter + Quote + selfExePath + Quote + Space + selfArgumentsStringList.join(Space);
        Global::inputLoopThreadAddress->receiveText(self_command);

        // Exit
        Global::qMainWindow->exitRequested = true;
        Global::inputLoopThreadAddress->receiveText(Command_Level1::exit);
    }

    void test()
    {
        using namespace Const_Input::Message;
        StdOut::printLine(Test);
    }
}

namespace ConsoleCommandFunction_Level2
{
    void run_quiet(QString command)
    {
        StartProcess::startProcess(command);
    }

    void run(QString command)
    {
        using namespace Const_Input::Message;

        StdOut::printLine(TryingToRun1);
        StdOut::printLine(TryingToRun2 + command);

        run_quiet(command);
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
        {Command_Level1::traydc, &ConsoleCommandFunction_Level1::traydc},
        {Command_Level1::expiresc, &ConsoleCommandFunction_Level1::expiresc}});
QMap<QString, void (*)(QString)> LoopThread::commandMap_level2(
    std::map<QString, void (*)(QString)>{
        {Command_Level2::run, &ConsoleCommandFunction_Level2::run},
        {Command_Level2::run_quiet, &ConsoleCommandFunction_Level2::run_quiet}});
