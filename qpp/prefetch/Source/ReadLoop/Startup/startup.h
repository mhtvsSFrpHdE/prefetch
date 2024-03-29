#ifndef ReadLoopStartup_h
#define ReadLoopStartup_h

#include <QThread>

class ReadLoop_Startup : public QThread
{
public:
    static void init();

    // This function will only run once
    static void (*startOnce)();

private:
    static void _startOnce();
    static void startOnce_remove();
};

#endif
