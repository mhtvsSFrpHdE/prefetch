#ifndef Translate_Tool_h
#define Translate_Tool_h

#include <QString>

// Global static access to Qt translate function `tr`
// Namespace variable can't use the macro for class variable
class TranslateTool
{
public:
    // Emulate Qt tr behavior at runtime
    static QString _tr(const char *className, const char *text);

private:
    // Disallow creating an instance of this object
    TranslateTool() {}
};

#include "translate_define.h"

#endif
