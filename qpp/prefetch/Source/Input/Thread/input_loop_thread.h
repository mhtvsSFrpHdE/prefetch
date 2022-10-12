#ifndef InputLoopThread_h
#define InputLoopThread_h

#include <QThread>
#include <QMap>

class InputLoopThread : public QThread
{
    Q_OBJECT
public:
    InputLoopThread();

    void run() override;

public slots:
    // Input from remote
    void receiveText(QString input);

private:
    class ConsoleCommandFunction_Level1
    {
    public:
        static void pause();
        static void resume();
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
        static void lang(QString command);
    };

    // Convert stdin command to function pointer
    static QMap<QString, void (*)()>
        commandMap_level1;
    static QMap<QString, void (*)(QString)> commandMap_level2;
};

#endif
