#include "const_mainwindow_tdummy.cpp"

QString Const_MainWindow::ButtonText::SendCommand_PushButton = DEFINE_Send;

void Const_MainWindow::ButtonText::init()
{
    SendCommand_PushButton = trr(tscope, DEFINE_Send);
}
