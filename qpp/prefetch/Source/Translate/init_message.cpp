#include "translator_loader.h"
#include "..\Core\const_core.h"
#include "..\Global\const_global.h"
#include "..\Input\const_input.h"
#include "..\Interface\MainWindow\const_mainwindow.h"
#include "..\Output\const_log.h"
#include "..\Setting\const_setting.h"

void TranslatorLoader::initMessage()
{
    Const_Global::CommonString::init();

    Const_Core::Message::init();
    Const_Input::Message::init();
    Const_Input::Command_Level2::init();
    Const_MainWindow::ButtonText::init();
    Const_Log::Message::init();
    Const_Setting::init();
}
