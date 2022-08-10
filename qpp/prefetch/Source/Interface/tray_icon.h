#include <QSystemTrayIcon>

// Static class
class TrayIcon
{
public:
    // Create system tray icon object
    static void init();

    // Show system tray icon
    static void start();

private:
    static QSystemTrayIcon *systemTrayIcon;

    // Disallow creating an instance of this object
    TrayIcon() {}
};