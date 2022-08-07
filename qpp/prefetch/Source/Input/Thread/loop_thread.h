#include <QThread>

class LoopThread : public QThread
{
    Q_OBJECT
public:
    LoopThread();

    void run();
};