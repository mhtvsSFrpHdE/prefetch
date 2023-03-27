#ifndef Const_Global_h
#define Const_Global_h

#include <QString>

// This file should independently to others
// Global must always available
//
// Linux GCC compiler doesn't accept nest static init more than ONCE
// On Windows mingw-w64 below code is work though
// For example
//     const string GlobalEmptyString = "";
//     const string Setting_EmptyString = GlobalEmptyString;    // Fine
//     const string MyEmptyString = Setting_EmptyString;    // <- This will not work
// https://stackoverflow.com/questions/15948274/static-qstring-initialization-fail
// http://www.parashift.com/c++-faq/static-init-order.html
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
