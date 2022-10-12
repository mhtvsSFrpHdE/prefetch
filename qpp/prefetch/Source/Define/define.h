// In prefetch.pro, there is `CONFIG += console` compile option
// This option will enable system native console, just like a typical Qt console application
// However:
//     - The console is not controllable (show/hide) without platform specified API
//     - Without console, stdin readline is non-blocking, which ruins related while loop
//          can cause program to no response
//     - Qt usually print runtime information like signal/slot error to console
//
// Therefore, the console will only use for debug purpose
// Compile with `CONFIG += console` and `CONSOLE_ENABLED true` to enable console
// Otherwize for a user release, keep `CONSOLE_ENABLED false`
#ifndef CONSOLE_ENABLED
#define CONSOLE_ENABLED false
#endif

// Add "Test" to tray menu, a handy place to execute some random fancy stuff
#ifndef TEST_TRAY_MENU_ENABLED
#define TEST_TRAY_MENU_ENABLED false
#endif

// Load and run log
//     When set to true, print to stdout also sync to log file
#ifndef LOG_ENABLED
#define LOG_ENABLED false
#endif

// Try to report last known position to log
//     This function designed to find crash in release (usually no gdb attached)
#ifndef LAST_KNOWN_POSITION_ENABLED
#define LAST_KNOWN_POSITION_ENABLED true
#endif

// Misc

#ifndef SKIP_STARTUP_ITEM
#define SKIP_STARTUP_ITEM false
#endif

#ifndef TRANSLATE_ENABLED
#define TRANSLATE_ENABLED true
#endif
