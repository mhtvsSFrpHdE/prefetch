#include "read_thread_crtrt.h"
#include "..\..\..\Setting\setting.h"
#include "..\..\..\Setting\const_setting.h"
#include "const_crtrt.h"

void ReadThread::init()
{
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Thread_ConfigKeyName;
    using namespace Const_ReadThread;

    // Get read buffer size from config
    auto getReadBufferSize = Setting::getInt(Thread, ReadBufferSize, Setting::setting);
    sharedReadBufferSize = getReadBufferSize.result;

    // Confirm useBuffer
    useBuffer = sharedReadBufferSize > 0;
    if (useBuffer)
    {
        // Convert read buffer size
        sharedReadBufferSize = getReadBufferSize.result * MegabyteMultiplier;

        // Read action function pointer
        run_read_action = &run_read_WithBuffer;
    }
    // Buffer not enabled
    else
    {
        // Read action function pointer
        run_read_action = &run_read_Directly;
    }
}
