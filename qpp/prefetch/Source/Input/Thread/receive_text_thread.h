#ifndef ReceiveTextThread_h
#define ReceiveTextThread_h

#include <QThread>
#include <QMap>

// This class delete itself after run function is done
class ReceiveTextThread : public QThread
{
    Q_OBJECT
public:
    ReceiveTextThread(QString input, void (*callback)() = NULL);

    void (*callback)();

    void run() override;

private:
    QString input;

    void run_callback();

    class ConsoleCommandFunction_Level1
    {
    public:
        static void stop();
        static void start();
        static void exit_quiet();
        static void exit();
        static void traydc();
        static void expiresc();
        static void test();
    };
    class ConsoleCommandFunction_Level2
    {
    public:
        static void run_quiet(QString command);
        static void run(QString command);
        static void lang_onUiThread(void *value);
        static void lang(QString command);
    };

    // Convert stdin command to function pointer
    static QMap<QString, void (*)()> commandMap_level1;
    static QMap<QString, void (*)(QString)> commandMap_level2;

    // Disallow create without input string
    ReceiveTextThread();
};

#endif
