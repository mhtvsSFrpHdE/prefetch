#include "parent_define.h"
#include "..\..\..\..\Input\const_input.h"
#include "..\..\..\..\Output\stdout.h"
#include "..\..\..\..\Core\ScanCache\scan_cache.h"
#include "..\..\..\..\Core\ReadFile\read_file_thread.h"
#include "..\..\..\..\Global\global.h"

void Parent_Prefetch::expiresc()
{
    using namespace Const_Input;
    using namespace Const_Input::Message;

    StdOut::printLine(TryingToExpireScanCache);

    if (Core_ScanCache::cacheFileExist == false)
    {
        StdOut::printLine(ScanCacheNotFound);
        return;
    }

    // Shutdown stdio
    StdOut::shutdown();

    // Stop running thread
    stop();
    Core::readThreadPool->waitForDone();

    // Delete cache file
    QFile::remove(Core_ScanCache::cacheFilePath);

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
    Global::qMainWindow->exitMutex.lock();
    Global::inputLoopThreadAddress->receiveText(Command_Level1::exit);
}
