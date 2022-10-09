#ifndef Translate_Tool_h
#define Translate_Tool_h

#include <QApplication>

// Global static access to Qt translate function `tr`
// Namespace variable can't use the macro for class variable
class TranslateTool
{
    Q_DECLARE_TR_FUNCTIONS(TranslateTool)
private:
    // Disallow creating an instance of this object
    TranslateTool() {}
};

#endif
