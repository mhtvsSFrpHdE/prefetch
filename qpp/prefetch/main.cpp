#include "Source\Global\global.h"
#include "Source\Input\stdin.h"

int main(int argc, char *argv[])
{
    Global::init(argc, argv);

    StdIn::start();

    Global::readFileLoopThreadAddress->start();

    TrayIcon::start();

    return Global::qGuiApplication->exec();
}
