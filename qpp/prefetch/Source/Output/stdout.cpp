#include "stdout.h"

QTextStream *StdOut::consoleOutput;

void StdOut::init()
{
    consoleOutput = new QTextStream(stdout);
}