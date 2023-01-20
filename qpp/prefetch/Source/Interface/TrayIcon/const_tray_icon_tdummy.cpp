#include "const_tray_icon.h"
#include "..\..\Translate\translate_tool.h"

#define tscope "Const_TrayIcon::MenuText"

void Const_TrayIcon::MenuText::tdummy()
{
#define DEFINE_Pause "Pause"
    Pause = tr("Pause");
#define DEFINE_Resume "Resume"
    Resume = tr("Resume");
#define DEFINE_Exit "Exit"
    Exit = tr("Exit");
}
