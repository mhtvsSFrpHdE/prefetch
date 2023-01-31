#include "read_thread.h"
#include "..\..\..\Setting\setting.h"
#include "..\..\..\Setting\const_setting.h"
#include "const_read_thread.h"

#define gn Const_Setting::ConfigGroupName
#define kn Const_Setting::ConfigKeyName::Thread
void ReadThread::init()
{
    using namespace Const_ReadThread;

    // Get read buffer size from config
    auto getReadBufferSize = Setting::getInt(gn::Thread, kn::ReadBufferSize, Setting::setting);
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
    stopMutex = new QMutex();
}
