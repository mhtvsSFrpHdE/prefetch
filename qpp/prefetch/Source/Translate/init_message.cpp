#include "translator_loader.h"
#include "..\Core\const_core.h"
#include "..\Global\const_global.h"
#include "..\Input\const_input.h"
#include "..\Interface\MainWindow\const_mainwindow.h"
#include "..\Output\const_log.h"
#include "..\Setting\const_setting.h"

void TranslatorLoader::initMessage()
{
    Const_Core::Message::init();
    Const_Input::Message::init();
    Const_MainWindow::ButtonText::init();
}
