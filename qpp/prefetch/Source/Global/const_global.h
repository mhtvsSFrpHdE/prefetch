#ifndef Const_Global_h
#define Const_Global_h

#include <QString>

// This file should independently to others
// Global must always available
namespace Const_Global
{
    namespace CommonString
    {
        const QString EmptyString = "";
        const QString Space = " ";
        const QString NewLine = "\n";
        const QString Tab = "    ";
        const QString Quote = "\"";
        const QString QtPathSplitter = "/";
        const QString DefaultValueType1 = "<default>";
        const QString StringListSplitterType1 = ",";
    }
}

#endif
