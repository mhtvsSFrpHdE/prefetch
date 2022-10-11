#include "translate_tool.h"
#include "..\Global\global.h"

QString TranslateTool::_tr(const char *className, const char *text)
{
    return Global::qGuiApplication->translate(className, text);
}
