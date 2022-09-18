#include <QString>

namespace Const_Input
{
    namespace Message
    {
        const QString InvalidCommand = "Invalid command";
        const QString TryingToPause = "Trying to pause prefetch";
        extern const QString PauseRequested;
        const QString TryingToResume = "Trying to resume prefetch";
        const QString TryingToExit1 = "Trying to exit prefetch";
        extern const QString TryingToExit2;
        const QString Test = "This function contain test code";
        const QString TryingToRun1 = "Trying to run program";
        extern const QString TryingToRun2;
        const QString TryingToExpireScanCache = "Trying to expire scan cache";
        extern const QString ExpireCacheRequested;
    }
    namespace Command_Level1
    {
        const QString pause = "pause";
        const QString resume = "resume";
        const QString test = "test";
        const QString exit = "exit";
        const QString traydc = "traydc";
        const QString expiresc = "expiresc";
    }
    namespace Command_Level2
    {
        extern const QString splitter;

        const QString run = "run";
        extern const QString run_withSplitter;
        const QString run_quiet = "run_quiet";
        extern const QString run_quiet_withSplitter;
    }
}
