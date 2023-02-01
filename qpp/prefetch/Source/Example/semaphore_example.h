#ifndef SemaphoreExample_h
#define SemaphoreExample_h

#include <QSemaphore>

#include "..\Output\log.h"

// QSemaphore doesn't provide an accessible copy constructor
// https://stackoverflow.com/questions/22659453/is-this-an-issue-with-mutable-member-qmutex-as-a-private-member
class SemaphoreExample
{
public:
    // Yes, create a semaphore but use as mutex
    static QSemaphore *getMutex()
    {
        auto semaphoreAddress = new QSemaphore(1);
        return semaphoreAddress;
    }

    static QSemaphore *getLockedSemaphore()
    {
        auto semaphoreAddress = new QSemaphore(0);
        return semaphoreAddress;
    }

    static void lock(QSemaphore *semaphore)
    {
        semaphore->acquire(1);
    }

    static bool tryLock(QSemaphore *semaphore)
    {
        return semaphore->tryAcquire(1);
    }

    static void unlock(QSemaphore *semaphore)
    {
        // Final check, program should end if global init doesn't find any translate file
        if (semaphore->available() > 0)
        {
            LAST_KNOWN_POSITION(2)
            // Have you forget something?
            throw std::runtime_error("UnlockingAvailableSemaphore");
        }
        semaphore->release(1);
    }

    static void unlockAnyway(QSemaphore *semaphore)
    {
        if (semaphore->available() > 0)
        {
            return;
        }
        semaphore->release(1);
    }

    static bool available(QSemaphore *semaphore)
    {
        return semaphore->available() > 0;
    }
};

#endif
