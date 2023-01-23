#include "mainwindow.h"
#include "..\..\Global\const_global.h"

void MainWindow::StdOut_print(QString textToPrint)
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

void MainWindow::StdOut_printLine(QString textToPrint)
{
    using namespace Const_Global::CommonString;
    emit print_signal(textToPrint + NewLine);

    // Save to line cache
    //
    // Print line is always make the cache clear
    lastKnownLineCommitted = true;
    lastKnownLine = textToPrint;
}

void MainWindow::StdOut_flush()
{
    // Mark line cache is clear
    lastKnownLineCommitted = true;
}
