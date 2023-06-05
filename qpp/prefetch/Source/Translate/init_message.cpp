#include "translator_loader.h"
#include "../ReadLoop/const_read_loop.h"
#include "../Input/const_input.h"
#include "../Interface/MainWindow/const_mainwindow.h"
#include "../Interface/TrayIcon/const_tray_icon.h"

void TranslatorLoader::initMessage()
{
    Const_ReadLoop::Message::init();
    Const_Input::Message::init();
    Const_MainWindow::ButtonText::init();
    Const_TrayIcon::MenuText::init();
}
