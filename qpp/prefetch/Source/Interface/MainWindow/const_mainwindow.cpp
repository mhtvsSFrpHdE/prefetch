#include "const_mainwindow.h"
#include "..\..\Translate\translate_tool.h"

QString Const_MainWindow::ButtonText::SendCommand_PushButton = NULL;

#define tscope "Const_MainWindow::ButtonText"
void Const_MainWindow::ButtonText::init()
{
    SendCommand_PushButton = trr(tscope, "Send");
}
void Const_MainWindow::ButtonText::tdummy()
{
    SendCommand_PushButton = tr("Send");
}
