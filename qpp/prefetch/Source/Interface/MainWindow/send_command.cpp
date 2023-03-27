#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Global/global.h"
#include "../../Output/log.h"
#include "../../Input/stdin.h"
#include "../../Example/semaphore_example.h"

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

void MainWindow::sendCommand_action_slot()
{
    // Lock mutex
    LAST_KNOWN_POSITION(3)
    bool locked = SemaphoreExample::tryLock(StdIn::freezeSemaphore);
    if (locked == false)
    {
        // Ignore request
        return;
    }

    StdIn::freeze();

    // Copy text
    auto command = ui->command_lineEdit->text();

    // Send to StdIn
    Global::inputLoopThreadAddress->receiveText_threaded(command, &StdInExample::restore_ordinary);

    // Clear command editor
    ui->command_lineEdit->clear();
}
