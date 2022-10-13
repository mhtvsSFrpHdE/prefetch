#ifndef Translate_Tool_h
#define Translate_Tool_h

#include <QString>
#include <QMutex>

// Redefining tr macro, any other include go first
// For example:
//     #include "..\Global\global.h"
//     #include "translate_tool.h"    // last one to include
//
// Global static access to Qt translate function `tr`
// Namespace variable can't use the macro for class variable
class TranslateTool
{
public:
    static QMutex *translateMutex;

    // Wrap access to translateMutex
    static void lock();

    // Wrap access to translateMutex
    static void unlock();

    // Emulate Qt tr behavior at runtime
    static QString _tr(const char *className, const char *text);
};

#include "translate_define.h"

#endif
