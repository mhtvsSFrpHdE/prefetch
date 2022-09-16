#include <QString>

namespace Const_Input
{
    namespace Message
    {
        const QString InvalidCommand = "Invalid command";
        const QString TryingToPause = "Trying to pause prefetch";
        const QString PauseRequested = "Pause has requested, good luck";
        const QString TryingToResume = "Trying to resume prefetch";
        const QString TryingToExit1 = "Trying to exit prefetch";
        extern const QString TryingToExit2;
        const QString Test = "This function contain test code";
        const QString TryingToRun1 = "Trying to run program";
        extern const QString TryingToRun2;
    }
    namespace Command_Level1
    {
        const QString pause = "pause";
        const QString resume = "resume";
        const QString test = "test";
        const QString exit = "exit";
        const QString traydc = "traydc";
    }
    namespace Command_Level2
    {
        extern const QString splitter;

        const QString run = "run";
        extern const QString run_withSplitter;
    }
}
