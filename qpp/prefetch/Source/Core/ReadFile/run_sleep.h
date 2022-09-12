// Wrapper to access QThread functions
class Run_Sleep
{
public:
    static void sleep(unsigned long secs);

private:
    // Disallow creating an instance of this object
    Run_Sleep();
};