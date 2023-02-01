#ifndef Const_Read_Thread_h
#define Const_Read_Thread_h

#include <QString>

namespace Const_ReadFileThread
{
    // %1: Qt format path, something like "C:/"
    const QString SearchPatternTemplate = "%1*";

    // ReadBufferSize in MB
    const int MegabyteMultiplier = 1024 * 1024;
}

#endif
