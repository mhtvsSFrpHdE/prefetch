#include <QMutex>
#include "../Global/global.h"

#include "translate_tool.h" // <- last one to include

QMutex *TranslateTool::translateMutex = new QMutex();

void TranslateTool::lock()
{
    translateMutex->lock();
}

void TranslateTool::unlock()
{
    translateMutex->unlock();
}

QString TranslateTool::_tr(const char *className, const char *text)
{
    return Global::qGuiApplication->translate(className, text);
}
