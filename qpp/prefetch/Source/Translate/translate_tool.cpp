// Redefining tr macro, any other include go first
#include "..\Global\global.h"

#include "translate_tool.h"

QString TranslateTool::_tr(const char *className, const char *text)
{
    return Global::qGuiApplication->translate(className, text);
}
