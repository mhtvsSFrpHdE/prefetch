#ifndef StdIn_h
#define StdIn_h

#include <QSemaphore>

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

    // Prevent "click multiple times simultaneously"
    static QSemaphore *freezeSemaphore;

    // Any init code
    static void init();

    // Start read loop
    // This method is NOT blocking
    static void start();

    // Freeze stdin related code entry
    static void freeze();
    static void restore();
};

#endif
