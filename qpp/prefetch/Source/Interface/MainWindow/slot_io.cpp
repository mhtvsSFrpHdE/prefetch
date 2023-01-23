#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"

void MainWindow::print_slot(QString textToPrint)
{
    // Make sure text is inserted after last character
    // User may copy text to clipboard, so cursor position is changed
    auto cursor = ui->stdOut_plainTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->stdOut_plainTextEdit->setTextCursor(cursor);

    ui->stdOut_plainTextEdit->insertPlainText(textToPrint);
}

void MainWindow::sendCommand_slot()
{
    // Copy text
    auto command = ui->command_lineEdit->text();

    // Send to StdIn
    Global::inputLoopThreadAddress->receiveText(command);

    // Clear command editor
    ui->command_lineEdit->clear();
}
