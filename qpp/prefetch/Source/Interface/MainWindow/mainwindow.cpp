#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\TrayIcon\tray_icon.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *closeEventAddress)
{
    TrayIcon::stop();
}
