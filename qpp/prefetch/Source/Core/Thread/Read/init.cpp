#include "read_thread.h"
#include "..\..\..\Setting\setting.h"
#include "..\..\..\Setting\const_setting.h"
#include "const_read_thread.h"

void ReadThread::init()
{
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Thread_ConfigKeyName;
    using namespace Const_ReadThread;

    // Get read buffer size from config
    auto getReadBufferSize = Setting::getInt(Thread, ReadBufferSize, Setting::setting);
    sharedReadBufferSize = getReadBufferSize.result;

    // Confirm useBuffer
    bool useBuffer = sharedReadBufferSize > 0;
    if (useBuffer)
    {
        // Convert read buffer size
        sharedReadBufferSize = getReadBufferSize.result * MegabyteMultiplier;

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

    // Create mutex
    pauseMutex = new QMutex();
}
