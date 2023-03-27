#include "const_input.h"
#include "../Translate/translate_tool.h"

#define tscope "Const_Input::Message"

void Const_Input::Message::tdummy()
{
#define DEFINE_InvalidCommand "Invalid command"
    InvalidCommand = tr("Invalid command");
#define DEFINE_TryingToStop "Trying to stop prefetch"
    TryingToStop = tr("Trying to stop prefetch");
#define DEFINE_StopRequested "Stop has requested, good luck"
    StopRequested = tr("Stop has requested, good luck");
#define DEFINE_TryingToStart "Trying to start prefetch"
    TryingToStart = tr("Trying to start prefetch");
#define DEFINE_TryingToExit1 "Trying to exit prefetch"
    TryingToExit1 = tr("Trying to exit prefetch");
#define DEFINE_TryingToExit2 "This can take a while in some case"
    TryingToExit2 = tr("This can take a while in some case");
#define DEFINE_Test "This function contain test code"
    Test = tr("This function contain test code");
#define DEFINE_TryingToRun1 "Trying to run program"
    TryingToRun1 = tr("Trying to run program");
#define DEFINE_TryingToExpireScanCache "Trying to expire scan cache"
    TryingToExpireScanCache = tr("Trying to expire scan cache");
#define DEFINE_ScanCacheNotFound "Scan cache not found, ignore"
    ScanCacheNotFound = tr("Scan cache not found, ignore");
#define DEFINE_TryingToLoadTranslate "Trying to load translate: "
    TryingToLoadTranslate = tr("Trying to load translate: ");
#define DEFINE_FailedToLoadTranslate "Failed to load translate: "
    FailedToLoadTranslate = tr("Failed to load translate: ");
#define DEFINE_TranslateFileLoaded "Translate file loaded: "
    TranslateFileLoaded = tr("Translate file loaded: ");
}
