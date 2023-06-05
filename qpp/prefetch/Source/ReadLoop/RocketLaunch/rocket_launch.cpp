#include "rocket_launch.h"
#include "../../Global/global.h"
#include "../../Input/const_input.h"
#include "../../Example/semaphore_example.h"
#include "../../Output/log.h"

void (*Core_RocketLaunch::rocketLaunch_action)();

void Core_RocketLaunch::rocketLaunch_exit()
{
    using namespace Const_Input;

    LAST_KNOWN_POSITION(2)

    Global::inputLoopThreadAddress->receiveText_threaded(Command_Level1::exit);

    // Block execute, never return
    auto blockSemaphore = SemaphoreExample::getLockedSemaphore();
    SemaphoreExample::lock(blockSemaphore);
}

void Core_RocketLaunch::init()
{
    bool rocketLaunch = Global::commandLineArgumentAddress->getRocketLaunch();
    if (rocketLaunch)
    {
        rocketLaunch_action = &rocketLaunch_exit;
    }
    else
    {
        rocketLaunch_action = &Global::dummyFunction;
    }
}
