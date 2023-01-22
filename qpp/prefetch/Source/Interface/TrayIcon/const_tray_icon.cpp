#include "const_tray_icon_tdummy.cpp"

QString Const_TrayIcon::MenuText::Stop = DEFINE_Stop;
QString Const_TrayIcon::MenuText::Start = DEFINE_Start;
QString Const_TrayIcon::MenuText::Exit = DEFINE_Exit;

void Const_TrayIcon::MenuText::init()
{
    Stop = trr(tscope, DEFINE_Stop);
    Start = trr(tscope, DEFINE_Start);
    Exit = trr(tscope, DEFINE_Exit);
}
