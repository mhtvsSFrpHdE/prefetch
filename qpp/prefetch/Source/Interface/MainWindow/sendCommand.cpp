#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"
#include "..\..\Output\log.h"

void MainWindow::sendCommand_freeze_slot()
{
    ui->sendCommand_pushButton->setEnabled(false);
    ui->command_lineEdit->setEnabled(false);
}

void MainWindow::sendCommand_restore_slot()
{
    ui->sendCommand_pushButton->setEnabled(true);
    ui->command_lineEdit->setEnabled(true);
}

// UI thread callback function
// Target: sendCommand_restore_slot
void sendCommand_restore_slot_toOrdinary()
{
    Global::qMainWindow->sendCommand_restore_slot();
}

void MainWindow::sendCommand_restore()
{
    emit callbackOnUiThread_signal(&sendCommand_restore_slot_toOrdinary);
}

// Input loop callback function
// Target: sendCommand_restore
void sendCommand_restore_callback_toOrdinary()
{
    Global::qMainWindow->sendCommand_restore();
}

void MainWindow::sendCommand_action_slot()
{
    // Lock mutex
    LAST_KNOWN_POSITION(3)
    sendCommand_freezeMutex->lock();

    // Disable button
    sendCommand_freeze_slot();

    // Copy text
    auto command = ui->command_lineEdit->text();

    // Send to StdIn
    Global::inputLoopThreadAddress->receiveText(command, &sendCommand_restore_callback_toOrdinary);

    // Clear command editor
    ui->command_lineEdit->clear();

    // Release mutex
    LAST_KNOWN_POSITION(4)
    sendCommand_freezeMutex->unlock();
}
