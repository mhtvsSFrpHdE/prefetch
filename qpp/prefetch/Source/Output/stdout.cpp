#include "stdout.h"
#include "..\Global\global.h"
#include "..\Global\const.h"

QTextStream *StdOut::consoleOutput;

void StdOut::init()
{
    consoleOutput = new QTextStream(stdout);
}

void StdOut::print(QString textToPrint)
{
    *consoleOutput << textToPrint;

    Global::qMainWindow->StdOut_print(textToPrint);
}

void StdOut::printLine(QString textToPrint)
{
    *consoleOutput << textToPrint
                   << endl;
    flush();

    Global::qMainWindow->StdOut_printLine(textToPrint);
}

void StdOut::printEndl()
{
    *consoleOutput << endl;

    using namespace Const_Global::CommonString;
    Global::qMainWindow->StdOut_print(NewLine);
}

void StdOut::flush()
{
    consoleOutput->flush();

    Global::qMainWindow->StdOut_flush();
}
