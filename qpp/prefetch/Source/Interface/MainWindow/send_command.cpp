#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"
#include "..\..\Output\log.h"
#include "..\..\Input\stdin.h"

void MainWindow::sendCommand_freeze()
{
    ui->sendCommand_pushButton->setEnabled(false);
    ui->command_lineEdit->setEnabled(false);
}

void MainWindow::sendCommand_restore()
{
    ui->sendCommand_pushButton->setEnabled(true);

    ui->command_lineEdit->setEnabled(true);
    ui->command_lineEdit->setFocus();
    // See KnownIssue for more details
    // QTimer::singleShot(0, ui->command_lineEdit, SLOT(setFocus()));
}

// Run sendCommand_restore on ui thread
void sendCommand_restore_callback_toOrdinary()
{
    Global::runOnUiThreadAddress->run(&StdIn::restore);
}

void MainWindow::sendCommand_action_slot()
{
    // Lock mutex
    LAST_KNOWN_POSITION(3)
    bool locked = StdIn::freezeMutex->tryLock();
    if (locked == false)
    {
        // Ignore request without hint right now
        // TODO
        return;
    }

    StdIn::freeze();

    // Copy text
    auto command = ui->command_lineEdit->text();

    // Send to StdIn
    Global::inputLoopThreadAddress->receiveText(command, &sendCommand_restore_callback_toOrdinary);

    // Clear command editor
    ui->command_lineEdit->clear();
}
