#include "parent_define.h"
#include "../../../../Input/const_input.h"
#include "../../../../Output/stdout.h"
#include "../../../../ReadLoop/ScanCache/scan_cache.h"
#include "../../../../ReadLoop/ReadFile/read_file_thread.h"
#include "../../../../Global/global.h"

void Parent_Prefetch::expiresc()
{
    using namespace Const_Input;
    using namespace Const_Input::Message;

    StdOut::printLine(TryingToExpireScanCache);

    if (ReadLoop_ScanCache::cacheFileExist == false)
    {
        StdOut::printLine(ScanCacheNotFound);
        return;
    }

    // Shutdown stdio
    StdOut::shutdown();

    // Stop running thread
    stop();
    ReadLoop::readThreadPool->waitForDone();

    // Delete cache file
    QFile::remove(ReadLoop_ScanCache::cacheFilePath);

    // Open self again

    // Add necessary arguments
    Global::commandLineArgumentAddress->setSkipStartup(true);
    Global::commandLineArgumentAddress->setShowMainWindow(true);

    // Send run quiet command
    //     `run `
    //   + `"<.exe>"`
    //   + `"<.ini>" <other flag>`
    auto self_command = Global::commandLineArgumentAddress->toString();
    Global::inputLoopThreadAddress->receiveText_threaded(self_command);

    // Exit
    Global::qMainWindow->exitMutex.lock();
    Global::inputLoopThreadAddress->receiveText_threaded(Command_Level1::exit);
}
