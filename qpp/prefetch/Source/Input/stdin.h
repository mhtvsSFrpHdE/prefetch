#ifndef StdIn_h
#define StdIn_h

#include "..\Define\define.h"

#if CONSOLE_ENABLED
#include <QTextStream>
#endif

class StdIn
{
public:
#if CONSOLE_ENABLED
    static QTextStream *consoleInput;
#endif

    // Any init code
    static void init();

    // Start read loop
    // This method is NOT blocking
    static void start();
};

#endif
