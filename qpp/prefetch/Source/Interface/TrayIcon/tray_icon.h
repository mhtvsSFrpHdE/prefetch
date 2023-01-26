#ifndef Tray_Icon_h
#define Tray_Icon_h

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
    // Update translate text
    void reloadTranslate();
    // Multi thread
    void freeze();
    void restore();

    // Show system tray icon
    static void start();

    // Remove system tray icon
    static void stop();

    static int trayMenuMinimalWidth;

public slots:
    void action_stop();
    void action_start();
    void action_exit();
    void action_traydc(QSystemTrayIcon::ActivationReason activationReason);
    void action_traydc_void();
    void action_test();
    void action_updateMenu(QSystemTrayIcon::ActivationReason activationReason);
    static void action_custom(void *command);

private:
    static QSystemTrayIcon *systemTrayIcon;
};

#endif
