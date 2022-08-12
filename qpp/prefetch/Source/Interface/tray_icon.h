#include <QSystemTrayIcon>

// In Qt 4, can't connect signals to static QObject class
// https://stackoverflow.com/questions/9428038/is-it-possible-to-connect-a-signal-to-a-static-slot-without-a-receiver-instance
//
// tray_icon.h will included in global.h
class TrayIcon : public QObject
{
    Q_OBJECT

public:
    // Create system tray icon object
    void init();

    // Show system tray icon
    static void start();

public slots:
    void action_pause();
    void action_resume();

private:
    static QSystemTrayIcon *systemTrayIcon;
};