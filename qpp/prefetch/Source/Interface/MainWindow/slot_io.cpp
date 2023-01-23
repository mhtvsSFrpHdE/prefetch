#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::print_slot(QString textToPrint)
{
    // Make sure text is inserted after last character
    // User may copy text to clipboard, so cursor position is changed
    auto cursor = ui->stdOut_plainTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->stdOut_plainTextEdit->setTextCursor(cursor);

    ui->stdOut_plainTextEdit->insertPlainText(textToPrint);
}
