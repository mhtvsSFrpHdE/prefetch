// Static class
class Startup
{
public:
    // This function will only run once
    static void startOnce();

private:
    // Disallow creating an instance of this object
    Startup() {}

    // After run set to true
    static bool started;
};
