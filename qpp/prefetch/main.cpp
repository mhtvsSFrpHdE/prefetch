#include "Source\Global\global.h"
#include "Source\Core\read_file.h"
#include "Source\Output\stdout.h"

int main(int argc, char *argv[])
{
    Global::init(argc, argv);

    ReadFile::start();

    return 0;
}
