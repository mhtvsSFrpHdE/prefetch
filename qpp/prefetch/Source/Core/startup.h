class Startup
{
public:
    static void init();

    // This function will only run once
    static void (*startOnce)();

private:
    static void _startOnce();
    static void startOnce_remove();
};
