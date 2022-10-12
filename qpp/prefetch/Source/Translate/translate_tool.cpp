#include "..\Global\global.h"

#include "translate_tool.h" // <- last one to include

QString TranslateTool::_tr(const char *className, const char *text)
{
    return Global::qGuiApplication->translate(className, text);
}
