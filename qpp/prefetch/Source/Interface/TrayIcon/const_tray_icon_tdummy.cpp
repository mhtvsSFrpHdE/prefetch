#include "const_tray_icon.h"
#include "..\..\Translate\translate_tool.h"

#define tscope "Const_TrayIcon::MenuText"

void Const_TrayIcon::MenuText::tdummy()
{
#define DEFINE_Stop "Stop"
    Stop = tr("Stop");
#define DEFINE_Start "Start"
    Start = tr("Start");
#define DEFINE_Exit "Exit"
    Exit = tr("Exit");
}
