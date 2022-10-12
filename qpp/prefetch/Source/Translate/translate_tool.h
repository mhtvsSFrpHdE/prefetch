#ifndef Translate_Tool_h
#define Translate_Tool_h

#include <QString>

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
    // Emulate Qt tr behavior at runtime
    static QString _tr(const char *className, const char *text);
};

#include "translate_define.h"

#endif
