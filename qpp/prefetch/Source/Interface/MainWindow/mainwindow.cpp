#include <QScrollBar>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"
#include "..\..\Setting\setting.h"
#include "..\Dpi\dpi.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize

    startToTray = Setting::getBool("Instance", "StartToTray", Setting::setting);
    minimizeToTray = Setting::getBool("Instance", "MinimizeToTray", Setting::setting);

    auto getPrintOffset = Setting::getInt("Instance", "PrintOffset", Setting::setting);
    printOffset = getPrintOffset.result;

    lastKnownLine = "";

    // Zoom
    Dpi::scale_qMainWindow(this);
    Dpi::scale_qWidgetRect(ui->stdOut_plainTextEdit);
    Dpi::scale_qWidgetRect(ui->command_lineEdit);
    Dpi::scale_qWidgetRect(ui->sendCommand_pushButton);

    // Log size limit to prevent memory leak
    auto getMaximumBlockCount = Setting::getInt("Instance", "MaximumBlockCount", Setting::setting);
    ui->stdOut_plainTextEdit->setMaximumBlockCount(getMaximumBlockCount.result);

    // Event

    // StdOut print
    connect(this, SIGNAL(print_signal(QString)), this, SLOT(print_slot(QString)));

    // Scroll bar to bottom on text change (after printed)
    connect(ui->stdOut_plainTextEdit, SIGNAL(textChanged()), this, SLOT(scrollBarToBottom_slot()));

    // StdIn send command

    // Send button
    connect(ui->sendCommand_pushButton, SIGNAL(clicked()), this, SLOT(sendCommand_slot()));
    // Enter on command edit
    connect(ui->command_lineEdit, SIGNAL(returnPressed()), this, SLOT(sendCommand_slot()));

    // Interface text

    // Get instance name
    auto instanceName = Setting::getString("Instance", "Name", Setting::setting);

    // MainWindow title
    setWindowTitle(instanceName);

    // Send command button text
    ui->sendCommand_pushButton->setText("Send");
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

void MainWindow::minimized_slot()
{
    // Check minimize to tray enabled
    if (minimizeToTray == false)
    {
        // No action on false
        return;
    }

    // Hide (minimize to tray)
    QTimer::singleShot(0, this, SLOT(hide()));
}

void MainWindow::restored_slot()
{
    // Restore and bring to front if minimized before hide
    setWindowState(Qt::WindowState::WindowActive);
}

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
    emit print_signal(textToPrint + "\n");

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

void MainWindow::start()
{
    if (startToTray == false)
    {
        this->show();
    }
}

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

void MainWindow::closeEvent(QCloseEvent *closeEventAddress)
{
    closeEventAddress->ignore();

    if (exitRequested)
    {
        return;
    }

    exitRequested = true;

    // Use command interface to do actual exit
    Global::inputLoopThreadAddress->receiveText("exit");
}

void MainWindow::changeEvent(QEvent *changeEventAddress)
{
    if (changeEventAddress->type() == QEvent::WindowStateChange)
    {
        // Minimize to tray
        if (isMinimized())
        {
            minimized_slot();
        }
    }
}

void MainWindow::showEvent(QShowEvent *showEventAddress)
{
    // Fix scroll bar position on restore
    ui->stdOut_plainTextEdit->insertPlainText("");
    scrollBarToBottom_slot();
};
