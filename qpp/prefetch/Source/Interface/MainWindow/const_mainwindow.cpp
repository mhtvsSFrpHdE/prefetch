#include "const_mainwindow.h"
#include "..\..\Translate\translate_tool.h"
#include "..\..\Translate\translate_define.h"

QString Const_MainWindow::ButtonText::SendCommand_PushButton = NULL;

void Const_MainWindow::ButtonText::init()
{
    SendCommand_PushButton = tr("Send");
}
