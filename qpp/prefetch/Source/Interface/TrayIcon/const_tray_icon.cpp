#include "const_tray_icon_tdummy.cpp"

QString Const_TrayIcon::MenuText::Pause = DEFINE_Pause;
QString Const_TrayIcon::MenuText::Resume = DEFINE_Resume;
QString Const_TrayIcon::MenuText::Exit = DEFINE_Exit;

void Const_TrayIcon::MenuText::init()
{
    Pause = trr(tscope, DEFINE_Pause);
    Resume = trr(tscope, DEFINE_Resume);
    Exit = trr(tscope, DEFINE_Exit);
}
