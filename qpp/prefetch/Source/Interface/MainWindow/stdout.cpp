#include "mainwindow.h"
#include "../../Global/const_global.h"
#include "../../Global/global.h"

void (*MainWindow::StdOut_print)(QString);
void (*MainWindow::StdOut_printLine)(QString);
void (*MainWindow::StdOut_flush)();

void MainWindow::StdOut_print_action(QString textToPrint)
{
    emit print_signal(textToPrint);

    // Save to line cache

    // If line cache is clear
    if (lastKnownLineCommitted)
    {
        // Set cache status to dirty
        lastKnownLineCommitted = false;
        // First statement, assign directly
        lastKnownLine = textToPrint;
    }
    // Line cache is dirty
    else
    {
        // Append to line cache
        lastKnownLine += textToPrint;
    }
}

void MainWindow::StdOut_printLine_action(QString textToPrint)
{
    using namespace Const_Global::CommonString;
    emit print_signal(textToPrint + NewLine);

    // Save to line cache
    //
    // Print line is always make the cache clear
    lastKnownLineCommitted = true;
    lastKnownLine = textToPrint;
}

void MainWindow::StdOut_flush_action()
{
    // Mark line cache is clear
    lastKnownLineCommitted = true;
}

void MainWindow::StdOut_print_redirect(QString textToPrint)
{
    Global::qMainWindow->StdOut_print_action(textToPrint);
}
void MainWindow::StdOut_printLine_redirect(QString textToPrint)
{
    Global::qMainWindow->StdOut_printLine_action(textToPrint);
}
void MainWindow::StdOut_flush_redirect()
{
    Global::qMainWindow->StdOut_flush_action();
}
