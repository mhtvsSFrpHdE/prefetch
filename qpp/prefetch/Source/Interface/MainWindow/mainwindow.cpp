#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(print_signal(QString)), this, SLOT(print_slot(QString)));

    // StdIn send command event

    // Send button
    connect(ui->sendCommand_pushButton, SIGNAL(clicked()), this, SLOT(sendCommand_slot()));
    // Enter on command edit
    connect(ui->command_lineEdit, SIGNAL(returnPressed()), this, SLOT(sendCommand_slot()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
