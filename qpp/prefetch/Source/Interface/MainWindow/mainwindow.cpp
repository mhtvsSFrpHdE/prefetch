#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\TrayIcon\tray_icon.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, SIGNAL(print_signal(QString)), this, SLOT(print_slot(QString)));
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
    ui->plainTextEdit->insertPlainText(textToPrint);
}

void MainWindow::closeEvent(QCloseEvent *closeEventAddress)
{
    TrayIcon::stop();
}
