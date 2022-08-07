#include <QThread>

class LoopThread : public QThread
{
public:
    LoopThread();

    void run();
};