// Redefining tr macro, any other include go first
//     For example:
//         #include "..\Global\global.h"
//         #include "translate_tool.h"    // <- last one to include
//
// Expand tr macro to non class scope (shortcut to static function)
//
// The tdummy (translate dummy) function:
//     Do not delete, the function spoof Qt lupdate parser
//     So the hard coded context:
//         `QT_TRANSLATE_NOOP("Namespace::Message", "Scan folder...")`
//     become:
//         `tr("Scan folder...")`
//     The class name may change in future, which will pretty handy
//
//     Usually, tdummy fill each variable with English translate text,
//     and create DEFINE_Variable name for later use
//         #define DEFINE_VariableName "English text"
//             VariableName = tr("English text");
//         #define DEFINE_Another "Another"
//             Another = tr("Another");
//     In this case, write translate only twice and close together
//
// Create a cpp file to wrap things together:
//     "const_mainwindow_tdummy.cpp"
//         #include "const_mainwindow.h"
//         #include "..\..\Translate\translate_tool.h"
//
//         #define tscope "Const_MainWindow::ButtonText"
//
//         void Const_MainWindow::ButtonText::tdummy()
//         {
//         #define DEFINE_VariableName "English text"
//             VariableName = tr("English text");
//         #define DEFINE_Another "Another"
//             Another = tr("Another");
//         }
//     "const_mainwindow.cpp"
//         // First line
//         #include "const_mainwindow_tdummy.cpp"
//
//         // Other cpp stuff
//         #include ...
#define tr(code) code

// Translate at run time
#define trr(className, text) \
    TranslateTool::_tr(className, text);
