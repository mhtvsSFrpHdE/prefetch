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
#define CONSOLE_ENABLED false

// Add "Test" to tray menu, a handy place to execute some random fancy stuff
#define TEST_TRAY_MENU_ENABLED false
