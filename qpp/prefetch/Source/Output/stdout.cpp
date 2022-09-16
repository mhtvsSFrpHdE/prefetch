#include "stdout.h"
#include "..\Global\global.h"
#include "..\Global\const_global.h"
#include "log.h"

QMutex StdOut::printLock(QMutex::NonRecursive);

QTextStream *StdOut::consoleOutput;

void StdOut::init()
{
    consoleOutput = new QTextStream(stdout);
}

void StdOut::print(QString textToPrint)
{
    lock();

    IF_LOG_ENABLED(*Log::logTextStream << textToPrint;)

    *consoleOutput << textToPrint;

    Global::qMainWindow->StdOut_print(textToPrint);

    unlock();
}

void StdOut::printLine(QString textToPrint)
{
    lock();

    IF_LOG_ENABLED(*Log::logTextStream << textToPrint
                                       << endl;)

    *consoleOutput << textToPrint
                   << endl;
    consoleOutput->flush();

    Global::qMainWindow->StdOut_printLine(textToPrint);

    unlock();
}

void StdOut::printEndl()
{
    lock();

    IF_LOG_ENABLED(*Log::logTextStream << endl;)

    *consoleOutput << endl;

    using namespace Const_Global::CommonString;
    Global::qMainWindow->StdOut_print(NewLine);

    unlock();
}

void StdOut::flush()
{
    lock();

    IF_LOG_ENABLED(Log::logTextStream->flush();)

    consoleOutput->flush();

    Global::qMainWindow->StdOut_flush();

    unlock();
}

void StdOut::lock()
{
    LAST_KNOWN_POSITION(3)
    printLock.lock();
}

void StdOut::unlock()
{
    printLock.unlock();
    LAST_KNOWN_POSITION(4)
}
