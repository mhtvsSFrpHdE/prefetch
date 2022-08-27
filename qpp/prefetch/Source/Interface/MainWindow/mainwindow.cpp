#include <QScrollBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"
#include "..\..\Setting\setting.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // StdOut print event
    connect(this, SIGNAL(print_signal(QString)), this, SLOT(print_slot(QString)));

    // Scroll bar to bottom on text change (after printed)
    connect(ui->stdOut_plainTextEdit, SIGNAL(textChanged()), this, SLOT(scrollBarToBottom_slot()));

    // StdIn send command event

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
    auto scrollBar = ui->stdOut_plainTextEdit->verticalScrollBar();
    auto scrollBarMaxSize = scrollBar->maximum();

    // Fix scroll bar position
    // Default maximum will left two empty line in text view
    scrollBarMaxSize = scrollBarMaxSize - 2;
    scrollBar->setValue(scrollBarMaxSize);
}

void MainWindow::StdOut_print(QString textToPrint)
{
    emit print_signal(textToPrint);
}

void MainWindow::StdOut_printLine(QString textToPrint)
{
    emit print_signal(textToPrint + "\n");
};

void MainWindow::print_slot(QString textToPrint)
{
    ui->stdOut_plainTextEdit->insertPlainText(textToPrint);
}

void MainWindow::sendCommand_slot()
{
    // Copy text
    auto command = ui->command_lineEdit->text();

    // Send to StdIn
    Global::inputLoopThreadAddress->receiveText(command);

    // Clear command editor
    emit ui->command_lineEdit->clear();
};

void MainWindow::closeEvent(QCloseEvent *closeEventAddress)
{
    TrayIcon::stop();
}
