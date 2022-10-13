#include <QMutex>

class Mutex
{
public:
    static void init();

    static QMutex *mutex;

    // Wrap access to mutex
    static void lock();

    // Wrap access to mutex
    static void unlock();

    static QMutex *getLockedMutex();
};
