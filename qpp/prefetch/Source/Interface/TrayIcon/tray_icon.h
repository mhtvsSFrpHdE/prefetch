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

    // Remove system tray icon
    static void stop();

public slots:
    void action_pause();
    void action_resume();
    void action_exit();
    void action_traydc(QSystemTrayIcon::ActivationReason activationReason);
    void action_traydc_void();
    void action_test();
    void action_updateMenu(QSystemTrayIcon::ActivationReason activationReason);
    static void action_custom(void *command);

private:
    static QSystemTrayIcon *systemTrayIcon;
};