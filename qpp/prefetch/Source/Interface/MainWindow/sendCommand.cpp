#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"

void MainWindow::sendCommand_freeze()
{
    ui->sendCommand_pushButton->setEnabled(false);
}

void MainWindow::sendCommand_restore()
{
    ui->sendCommand_pushButton->setEnabled(true);
}

void MainWindow::sendCommand_slot()
{
    // Disable button
    sendCommand_freeze();

    // Copy text
    auto command = ui->command_lineEdit->text();

    // Send to StdIn
    Global::inputLoopThreadAddress->receiveText(command);

    // Clear command editor
    ui->command_lineEdit->clear();
}
