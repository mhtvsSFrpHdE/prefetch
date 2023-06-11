#include "stdout.h"
#include "../Global/global.h"
#include "../Global/const_global.h"
#include "log.h"

QMutex StdOut::printLock(QMutex::NonRecursive);

QTextStream *StdOut::consoleOutput;

void StdOut::init()
{
    consoleOutput = new QTextStream(stdout);

    // StdOut init before MainWindow
    // skip sync output to MainWindow
    Global::qMainWindow->StdOut_print = &Global::dummyFunctionT<QString>;
    Global::qMainWindow->StdOut_printLine = &Global::dummyFunctionT<QString>;
    Global::qMainWindow->StdOut_flush = &Global::dummyFunction;
}

void (*StdOut::print_address)(QString) = &_print;
void (*StdOut::printLine_address)(QString) = &_printLine;
void (*StdOut::printEndl_address)() = &_printEndl;
void (*StdOut::flush_address)() = &_flush;

void StdOut::_print(QString textToPrint)
{
    lock();

    IF_LOG_ENABLED(*Log::logTextStream << textToPrint;)

    *consoleOutput << textToPrint;

    (*Global::qMainWindow->StdOut_print)(textToPrint);

    unlock();
}
void StdOut::print(QString textToPrint)
{
    (*print_address)(textToPrint);
}

void StdOut::_printLine(QString textToPrint)
{
    lock();

    IF_LOG_ENABLED(*Log::logTextStream << textToPrint
                                       << endl;)

    *consoleOutput << textToPrint
                   << endl;
    consoleOutput->flush();

    (*Global::qMainWindow->StdOut_printLine)(textToPrint);

    unlock();
}
void StdOut::printLine(QString textToPrint)
{
    (*printLine_address)(textToPrint);
}

void StdOut::_printEndl()
{
    lock();

    IF_LOG_ENABLED(*Log::logTextStream << endl;)

    *consoleOutput << endl;

    using namespace Const_Global::CommonString;
    (*Global::qMainWindow->StdOut_print)(NewLine);

    unlock();
}
void StdOut::printEndl()
{
    (*printEndl_address)();
}

void StdOut::_flush()
{
    lock();

    IF_LOG_ENABLED(Log::logTextStream->flush();)

    consoleOutput->flush();

    (*Global::qMainWindow->StdOut_flush)();

    unlock();
}
void StdOut::flush()
{
    (*flush_address)();
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

void StdOut::shutdown()
{
    LAST_KNOWN_POSITION(2)

    printLock.lock();

    print_address = &Global::dummyFunctionT;
    printLine_address = &Global::dummyFunctionT;
    printEndl_address = &Global::dummyFunction;
    flush_address = &Global::dummyFunction;

#if LOG_ENABLED
    Log::shutdown();
#endif

    printLock.unlock();
}
