// Expand tr macro to non class scope (shortcut to static function)
//
// Use tdummy (translate dummy) function:
//     Do not delete, the function spoof Qt lupdate parser
//     So the hard coded context:
//         `QT_TRANSLATE_NOOP("Namespace::Message", "Scan folder...")`
//     become:
//         `tr("Scan folder...")`
//     The class name may change in future, which will pretty handy
//
//     Usually, tdummy is a copy of related init function and should not get called
#define tr(code) code

// Translate at run time
#define trr(className, text) \
    TranslateTool::_tr(className, text);
