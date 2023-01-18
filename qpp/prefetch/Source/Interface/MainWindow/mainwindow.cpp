#include <QScrollBar>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Global\global.h"
#include "..\..\Global\const_global.h"
#include "..\..\Setting\setting.h"
#include "..\..\Setting\const_setting.h"
#include "..\Dpi\dpi.h"
#include "..\..\Input\const_input.h"
#include "const_mainwindow.h"
#include "..\..\Output\stdout.h"
#include "..\..\Output\log.h"
#include "..\..\Core\const_core.h"
#include "..\..\Translate\translate_tool.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    using namespace Const_Setting;
    using namespace Const_Setting::ConfigGroupName;
    using namespace Const_Setting::Instance_ConfigKeyName;
    using namespace Const_Setting::MainWindow_ConfigKeyName;
    using namespace Const_Global::CommonString;
    using namespace Const_MainWindow::ButtonText;
    using namespace Const_Core::Arg;

    ui->setupUi(this);

    // Initialize

    startToTray = Setting::getBool(Instance, StartToTray, Setting::setting);
    // Command line override
    if (Global::commandLineArgumentAddress->getShowMainWindow())
    {
        startToTray = false;
    }

    minimizeToTray = Setting::getBool(Instance, MinimizeToTray, Setting::setting);

    auto resizable = Setting::getBool(cgn_MainWindow, Resizable, Setting::setting);

    auto getPrintOffset = Setting::getInt(Instance, PrintOffset, Setting::setting);
    printOffset = getPrintOffset.result;

    auto sizeArray = Setting::getStringList(cgn_MainWindow, Size, Setting::setting);
    auto sizeWidth = sizeArray[0].toInt();
    auto sizeHeight = sizeArray[1].toInt();
    if (resizable)
    {
        this->setMinimumSize(sizeWidth, sizeHeight);
    }
    else
    {
        this->setFixedSize(sizeWidth, sizeHeight);
    }

    // If value was given, update position
    auto getPosition = Setting::getString(cgn_MainWindow, Position, Setting::setting);
    if (getPosition != MainWindow_Position_Value::Default)
    {
        auto positionArray = Setting::getStringList(cgn_MainWindow, Position, Setting::setting);
        this->move(positionArray[0].toInt(), positionArray[1].toInt());
    }

    lastKnownLine = EmptyString;

    // Zoom
    Dpi::scale_qMainWindow(this);
    Dpi::scale_qWidgetRect(ui->stdOut_plainTextEdit);
    Dpi::scale_qWidgetRect(ui->command_lineEdit);
    Dpi::scale_qWidgetRect(ui->sendCommand_pushButton);

    // Log size limit to prevent memory leak
    auto getMaximumBlockCount = Setting::getInt(Instance, MaximumBlockCount, Setting::setting);
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
    auto instanceName = Setting::getString(Instance, Name, Setting::setting);

    // MainWindow title
    setWindowTitle(instanceName);

    // Send command button text
    ui->sendCommand_pushButton->setText(SendCommand_PushButton);
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

void MainWindow::updateScrollBar_slot()
{
    // Fix scroll bar position on restore
    // If change text in QPlainTextEdit during window.hide()
    //     After show(), QPlainTextEdit's scroll bar will have wrong maximum() value
    //
    // ensureCursorVisible() only "scroll to cursor", but position still bad
    LAST_KNOWN_POSITION(0)
    StdOut::lock();

    auto existText = ui->stdOut_plainTextEdit->toPlainText();
    ui->stdOut_plainTextEdit->setPlainText(existText);
    scrollBarToBottom_slot();

    StdOut::unlock();
    LAST_KNOWN_POSITION(1)
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

    updateScrollBar_slot();
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
    using namespace Const_Global::CommonString;
    emit print_signal(textToPrint + NewLine);

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
    closeEventAddress->accept();

    if (exitRequested)
    {
        return;
    }
    exitRequested = true;

    // Use command interface to do actual exit
    using namespace Const_Input;
    Global::inputLoopThreadAddress->receiveText(Command_Level1::exit);
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

    if (changeEventAddress->type() == QEvent::LanguageChange)
    {
        using namespace Const_MainWindow::ButtonText;

        LAST_KNOWN_POSITION(3)
        TranslateTool::lock();

        ui->sendCommand_pushButton->setText(SendCommand_PushButton);

        TranslateTool::unlock();
        LAST_KNOWN_POSITION(4)
    }
}
