#include "Source\Global\global.h"
#include "Source\Input\stdin.h"
#include "Source\Output\log.h"

int main(int argc, char *argv[])
{
    Global::init(argc, argv);
    LAST_KNOWN_POSITION(0)

    StdIn::start();
    LAST_KNOWN_POSITION(2)

    Global::qMainWindow->start();
    LAST_KNOWN_POSITION(2)

    Global::coreLoopThreadAddress->start();
    LAST_KNOWN_POSITION(2)

    TrayIcon::start();
    LAST_KNOWN_POSITION(2)

    LAST_KNOWN_POSITION(1)
    return Global::qGuiApplication->exec();
}
