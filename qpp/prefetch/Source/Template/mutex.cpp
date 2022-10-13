#include "mutex.h"

QMutex *Mutex::mutex = getLockedMutex();

QMutex *Mutex::getLockedMutex()
{
    auto mutexAddress = new QMutex(QMutex::NonRecursive);
    mutexAddress->lock();
    return mutexAddress;
}

void Mutex::init()
{
    // Unlock mutex after init done
    unlock();
}

void Mutex::lock()
{
    mutex->lock();
}

void Mutex::unlock()
{
    mutex->unlock();
}
