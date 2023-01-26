#ifndef MutexExample_h
#define MutexExample_h

#include <QMutex>

class MutexExample
{
public:
    // QMutex doesn't provide an accessible copy constructor
    // https://stackoverflow.com/questions/22659453/is-this-an-issue-with-mutable-member-qmutex-as-a-private-member
    static QMutex *getLockedMutex()
    {
        auto mutexAddress = new QMutex(QMutex::NonRecursive);
        mutexAddress->lock();
        return mutexAddress;
    }
};

#endif
