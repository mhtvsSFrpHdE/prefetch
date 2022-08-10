#include "Source\Global\global.h"
#include "Source\Core\read_file.h"
#include "Source\Input\stdin.h"
#include "Source\Interface\tray_icon.h"

int main(int argc, char *argv[])
{
    Global::init(argc, argv);

    StdIn::start();

    ReadFile::start();

    return 0;
    TrayIcon::start();

}
