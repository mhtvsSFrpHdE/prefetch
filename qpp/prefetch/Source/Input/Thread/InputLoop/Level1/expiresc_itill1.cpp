#include "..\..\input_loop_thread.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\scan_cache.h"
#include "..\..\..\..\Core\ReadFile\read_file.h"
#include "..\..\..\..\Global\global.h"

#define Parent InputLoopThread::ConsoleCommandFunction_Level1

void Parent::expiresc()
{
    using namespace Const_Input;
    using namespace Const_Input::Message;

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

    // Add necessary arguments
    Global::commandLineArgumentAddress->setSkipStartup(true);
    Global::commandLineArgumentAddress->setShowMainWindow(true);

    // Send run quiet command
    //     `run `
    //   + `"<.exe>"`
    //   + `"<.ini>" <other flag>`
    auto self_command = Global::commandLineArgumentAddress->toString();
    Global::inputLoopThreadAddress->receiveText(self_command);

    // Exit
    Global::qMainWindow->exitRequested = true;
    Global::inputLoopThreadAddress->receiveText(Command_Level1::exit);
}
