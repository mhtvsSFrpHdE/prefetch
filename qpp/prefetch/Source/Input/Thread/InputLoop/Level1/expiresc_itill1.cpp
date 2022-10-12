#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Global\const_global.h"
#include "..\..\..\..\Core\const_core.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\scan_cache.h"
#include "..\..\..\..\Core\ReadFile\read_file.h"
#include "..\..\..\..\Global\global.h"
#include "..\..\..\..\Setting\setting.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::expiresc()
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
