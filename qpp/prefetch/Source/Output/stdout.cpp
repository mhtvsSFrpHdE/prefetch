#include "stdout.h"
#include "..\Global\global.h"
#include "..\Global\const_global.h"
#include "log.h"

QTextStream *StdOut::consoleOutput;

void StdOut::init()
{
    consoleOutput = new QTextStream(stdout);
}

void StdOut::print(QString textToPrint)
{

    IF_LOG_ENABLED(*Log::logTextStream << textToPrint;)

    *consoleOutput << textToPrint;

    Global::qMainWindow->StdOut_print(textToPrint);
}

void StdOut::printLine(QString textToPrint)
{
    IF_LOG_ENABLED(*Log::logTextStream << textToPrint
                                       << endl;)

    *consoleOutput << textToPrint
                   << endl;
    flush();

    Global::qMainWindow->StdOut_printLine(textToPrint);
}

void StdOut::printEndl()
{
    IF_LOG_ENABLED(*Log::logTextStream << endl;)

    *consoleOutput << endl;

    using namespace Const_Global::CommonString;
    Global::qMainWindow->StdOut_print(NewLine);
}

void StdOut::flush()
{
    IF_LOG_ENABLED(Log::logTextStream->flush();)

    consoleOutput->flush();

    Global::qMainWindow->StdOut_flush();
}
