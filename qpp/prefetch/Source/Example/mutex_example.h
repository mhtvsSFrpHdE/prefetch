#include <QMutex>

class MutexExample
{
public:
    static QMutex *getLockedMutex();
};

QMutex *MutexExample::getLockedMutex()
{
    auto mutexAddress = new QMutex(QMutex::NonRecursive);
    mutexAddress->lock();
    return mutexAddress;
}
