// In prefetch.pro, there is `CONFIG += console` compile option
// This option will enable system native console, just like a typical Qt console application
// However:
//     - The console is not controllable (show/hide) without platform specified API
//     - Without console, stdin readline is non-blocking, which ruins related while loop
//          can cause program to no response
//     - Qt usually print runtime information like signal/slot error to console
//
// Therefore, the console will only use for debug purpose
// Compile with `CONFIG += console` and `CONSOLE_ENABLED 1` to enable console
// Otherwize for a user release, keep `CONSOLE_ENABLED 0`
#define CONSOLE_ENABLED 0
