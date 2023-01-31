#include "const_core.h"
#include "..\Translate\translate_tool.h"

#define tscope "Const_Core::Message"

void Const_Core::Message::tdummy()
{
#define DEFINE_ScanFolder "Scan folder..."
    ScanFolder = tr("Scan folder...");
#define DEFINE_CacheFound "Cache found, restore file list"
    CacheFound = tr("Cache found, restore file list");
#define DEFINE_Prefetching "Prefetching..."
    Prefetching = tr("Prefetching...");
#define DEFINE_Idle_Time "Idle, Time: "
    Idle_Time = tr("Idle, Time: ");
#define DEFINE_Idle_Sec " Sec"
    Idle_Sec = tr(" Sec");
#define DEFINE_ScanFolder_Time "Scan complete, Time: "
    ScanFolder_Time = tr("Scan complete, Time: ");
#define DEFINE_CodeExecuteTimeFormatter ".zzz"
    CodeExecuteTimeFormatter = tr(".zzz");
#define DEFINE_RescanIntervalReached1 "Rescan interval reached."
    RescanIntervalReached1 = tr("Rescan interval reached.");
#define DEFINE_RescanIntervalReached2 "Cache will expire on next run."
    RescanIntervalReached2 = tr("Cache will expire on next run.");

#define DEFINE_RunStartupItems "Run startup items..."
    RunStartupItems = tr("Run startup items...");

#define DEFINE_SkipProcessDetected "Skip process detected"
    SkipProcessDetected = tr("Skip process detected");
}
