#include "Thread\loop_thread.h"

// Static class
class StdIn
{
public:
    static LoopThread *loopThreadAddress;

    // Any init code
    static void init();

    // Start read loop
    // This method is NOT blocking
    static void start();

private:
    // Disallow creating an instance of this object
    StdIn() {}
};