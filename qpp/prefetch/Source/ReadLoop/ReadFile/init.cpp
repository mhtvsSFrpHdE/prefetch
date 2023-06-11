#include "read_file_thread.h"
#include "../../Setting/setting.h"
#include "../../Setting/const_setting.h"
#include "const_read_file_thread.h"
#include "../../Example/semaphore_example.h"
#include "../../Global/global.h"

#define gn Const_Setting::ConfigGroupName
#define kn Const_Setting::ConfigKeyName::Thread
#define crft Const_ReadFileThread

void ReadLoop_ReadFileThread::init()
{
    // Get read buffer size from config
    auto getReadBufferSize = Setting::getInt(gn::Thread, kn::ReadBufferSize, Setting::setting);
    sharedReadBufferSize = getReadBufferSize.result;

    // Confirm useBuffer
    bool useBuffer = sharedReadBufferSize > 0;
    if (useBuffer)
    {
        // Convert read buffer size
        sharedReadBufferSize = getReadBufferSize.result * crft::MegabyteMultiplier;

        // Read action function pointer
        run_read_action = &run_read_WithBuffer;

        // Shared buffer action function pointer
        newSharedReadBuffer_action = &newSharedReadBuffer_WithBuffer;
        deleteSharedReadBuffer_action = &deleteSharedReadBuffer_WithBuffer;
    }
    // Buffer not enabled
    else
    {
        // Read action function pointer
        run_read_action = &run_read_Directly;

        // Shared buffer action function pointer
        newSharedReadBuffer_action = &newSharedReadBuffer_Directly;
        deleteSharedReadBuffer_action = &deleteSharedReadBuffer_Directly;
    }

    // Confirm scanOnly (it can override useBuffer results)
    bool scanOnly = Global::commandLineArgumentAddress->getScanOnly();
    if (scanOnly)
    {
        // Read action function pointer
        run_read_action = &run_read_ScanOnly;

        // Shared buffer action function pointer
        newSharedReadBuffer_action = &newSharedReadBuffer_ScanOnly;
        deleteSharedReadBuffer_action = &deleteSharedReadBuffer_ScanOnly;
    }

    // Create semaphore
    stopSemaphore = SemaphoreExample::getMutex();
}
