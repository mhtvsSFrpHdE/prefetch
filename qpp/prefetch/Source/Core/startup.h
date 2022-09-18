// Static class
class Startup
{
public:
    static void init(int argc, QStringList argv);

    // This function will only run once
    static void (*startOnce)();

private:
    // Disallow creating an instance of this object
    Startup() {}

    static void _startOnce();
    static void startOnce_remove();

    static void dummyFunction();
};
