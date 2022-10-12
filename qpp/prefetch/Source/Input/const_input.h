#ifndef Const_Input_h
#define Const_Input_h

#include <QString>

namespace Const_Input
{
    namespace Message
    {
        extern QString InvalidCommand;
        extern QString TryingToPause;
        extern QString PauseRequested;
        extern QString TryingToResume;
        extern QString TryingToExit1;
        extern QString TryingToExit2;
        extern QString Test;
        extern QString TryingToRun1;
        extern QString TryingToRun2;
        extern QString TryingToExpireScanCache;
        extern QString ScanCacheNotFound;
        extern QString TryingToLoadTranslate;
        const QString TranslateNotAvailable = "Translate is not enabled in this build.";

        extern void init();

        // See translate_define.h for more information
        extern void tdummy();
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
        extern QString splitter;

        const QString run = "run";
        extern const QString run_withSplitter;
        const QString run_quiet = "run_quiet";
        extern const QString run_quiet_withSplitter;
        const QString lang = "lang";
    }
}

#endif
