#include <QScrollBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Output/log.h"
#include "../../Output/stdout.h"

void MainWindow::scrollBarToBottom_slot()
{
    // Background update is not necessary
    if (isVisible() == false)
    {
        return;
    }

    auto scrollBar = ui->stdOut_plainTextEdit->verticalScrollBar();
    auto scrollBarMaxSize = scrollBar->maximum();

    // Fix scroll bar position
    // Default maximum will left two empty line in text view
    scrollBarMaxSize = scrollBarMaxSize - printOffset;
    scrollBar->setValue(scrollBarMaxSize);
}

void MainWindow::updateScrollBar_slot()
{
    // Fix scroll bar position on restore
    // If change text in QPlainTextEdit during window.hide()
    //     After show(), QPlainTextEdit's scroll bar will have wrong maximum() value
    //
    // ensureCursorVisible() only "scroll to cursor", but position still bad
    LAST_KNOWN_POSITION(0)
    StdOut::lock();

    auto existText = ui->stdOut_plainTextEdit->toPlainText();
    ui->stdOut_plainTextEdit->setPlainText(existText);
    scrollBarToBottom_slot();

    StdOut::unlock();
    LAST_KNOWN_POSITION(1)
}
