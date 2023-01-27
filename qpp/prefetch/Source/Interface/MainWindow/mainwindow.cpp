#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\..\Setting\setting.h"
#include "..\..\Setting\const_setting.h"
#include "..\..\Global\global.h"
#include "..\..\Global\const_global.h"
#include "..\Dpi\dpi.h"
#include "const_mainwindow.h"
#include "..\..\Input\const_input.h"
#include "..\..\Output\log.h"
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

    ui->setupUi(this);

    // Initialize

    // Start to tray
    {
        startToTray = Setting::getBool(Instance, StartToTray, Setting::setting);

        // Command line override
        bool commandLineOverride = Global::commandLineArgumentAddress->getShowMainWindow();
        if (commandLineOverride)
        {
            startToTray = false;
        }
    }

    // Minimize to try
    {
        minimizeToTray = Setting::getBool(Instance, MinimizeToTray, Setting::setting);
    }

    // Resizeable
    {
        auto resizable = Setting::getBool(cgn_MainWindow, Resizable, Setting::setting);
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
    }

    // Print offset
    {
        auto getPrintOffset = Setting::getInt(Instance, PrintOffset, Setting::setting);
        printOffset = getPrintOffset.result;
    }

    // Position
    {

        // If value was given, update position
        auto getPosition = Setting::getString(cgn_MainWindow, Position, Setting::setting);
        if (getPosition != MainWindow_Position_Value::Default)
        {
            auto positionArray = Setting::getStringList(cgn_MainWindow, Position, Setting::setting);
            this->move(positionArray[0].toInt(), positionArray[1].toInt());
        }
    }

    // Last known line
    {
        lastKnownLine = EmptyString;
    }

    // Zoom
    {
        Dpi::scale_qMainWindow(this);
        Dpi::scale_qWidgetRect(ui->stdOut_plainTextEdit);
        Dpi::scale_qWidgetRect(ui->command_lineEdit);
        Dpi::scale_qWidgetRect(ui->sendCommand_pushButton);
    }

    // Log size limit to prevent memory leak
    {
        auto getMaximumBlockCount = Setting::getInt(Instance, MaximumBlockCount, Setting::setting);
        ui->stdOut_plainTextEdit->setMaximumBlockCount(getMaximumBlockCount.result);
    }

    // Event
    {

        // StdOut print
        connect(this, SIGNAL(print_signal(QString)), this, SLOT(print_slot(QString)));

        // Scroll bar to bottom on text change (after printed)
        connect(ui->stdOut_plainTextEdit, SIGNAL(textChanged()), this, SLOT(scrollBarToBottom_slot()));

        // Send button
        {
            // Click
            connect(ui->sendCommand_pushButton, SIGNAL(clicked()), this, SLOT(sendCommand_action_slot()));
            // Enter on command edit
            connect(ui->command_lineEdit, SIGNAL(returnPressed()), this, SLOT(sendCommand_action_slot()));
        }
    }

    // Interface text
    {
        // Get instance name
        auto instanceName = Setting::getString(Instance, Name, Setting::setting);

        // MainWindow title
        setWindowTitle(instanceName);

        // Send command button text
        ui->sendCommand_pushButton->setText(SendCommand_PushButton);
    }

    // Focus command editor
    {
        ui->command_lineEdit->setFocus();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *closeEventAddress)
{
    // Do not forward event to other handler
    closeEventAddress->accept();

    // If exit mutex unavailable, do nothing
    bool exitMutexLocked = exitMutex.tryLock();
    if (exitMutexLocked == false)
    {
        return;
    }
    // Mutex locked

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

        Global::trayIconInstanceAddress->reloadTranslate();

        TranslateTool::unlock();
        LAST_KNOWN_POSITION(4)
    }
}

void MainWindow::start()
{
    if (startToTray == false)
    {
        this->show();
    }
}
