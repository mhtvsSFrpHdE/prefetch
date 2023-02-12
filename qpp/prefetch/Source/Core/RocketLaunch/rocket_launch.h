class Core_RocketLaunch
{
public:
    // Any init code
    static void init();

    // Redirect exit function at runtime
    static void (*rocketLaunch_action)();

private:
    // If rocket launch is enabled, send exit command
    static void rocketLaunch_exit();
    static void rocketLaunch_ignore();
};
