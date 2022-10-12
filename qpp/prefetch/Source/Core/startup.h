class Startup
{
public:
    static void init(int argc, QStringList argv);

    // This function will only run once
    static void (*startOnce)();

private:
    static void _startOnce();
    static void startOnce_remove();
};
