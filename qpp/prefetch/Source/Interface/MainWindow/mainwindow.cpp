#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../Setting/setting.h"
#include "../../Setting/const_setting.h"
#include "../../Global/global.h"
#include "../../Global/const_global.h"
#include "../Dpi/dpi.h"
#include "const_mainwindow.h"
#include "../../Input/const_input.h"
#include "../../Output/log.h"
#include "../../Translate/translate_tool.h"

#define gn Const_Setting::ConfigGroupName
#define ikn Const_Setting::ConfigKeyName::Instance
#define mkn Const_Setting::ConfigKeyName::MainWindow
#define mpv Const_Setting::Value::MainWindow::Position

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    using namespace Const_Setting;
    using namespace Const_Global::CommonString;
    using namespace Const_MainWindow::ButtonText;

    ui->setupUi(this);

    // Initialize

    // Start to tray
    {
        startToTray = Setting::getBool(gn::Instance, ikn::StartToTray, Setting::setting);

        // Command line override
        bool commandLineOverride = Global::commandLineArgumentAddress->getShowMainWindow();
        if (commandLineOverride)
        {
            startToTray = false;
        }
    }

    // Minimize to try
    {
        minimizeToTray = Setting::getBool(gn::Instance, ikn::MinimizeToTray, Setting::setting);
    }

    // Resizeable
    {
        auto resizable = Setting::getBool(gn::Instance_MainWindow, mkn::Resizable, Setting::setting);
        auto sizeArray = Setting::getStringList(gn::Instance_MainWindow, mkn::Size, Setting::setting);
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
        auto getPrintOffset = Setting::getInt(gn::Instance, ikn::PrintOffset, Setting::setting);
        printOffset = getPrintOffset.result;
    }

    // Position
    {
        // If value was given, update position
        auto getPosition = Setting::getString(gn::Instance_MainWindow, mkn::Position, Setting::setting);
        if (getPosition != mpv::Default)
        {
            auto positionArray = Setting::getStringList(gn::Instance_MainWindow, mkn::Position, Setting::setting);
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
        auto getMaximumBlockCount = Setting::getInt(gn::Instance, ikn::MaximumBlockCount, Setting::setting);
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
        auto instanceName = Setting::getString(gn::Instance, ikn::Name, Setting::setting);

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
    Global::inputLoopThreadAddress->receiveText_threaded(Command_Level1::exit);
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
