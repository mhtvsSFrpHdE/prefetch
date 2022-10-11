#include "const_input.h"
#include "..\Global\const_global.h"
#include "..\Translate\translate_tool.h"

using namespace Const_Input;

QString Message::InvalidCommand = NULL;
QString Message::TryingToPause = NULL;
QString Message::PauseRequested = NULL;
QString Message::TryingToResume = NULL;
QString Message::TryingToExit1 = NULL;
QString Message::TryingToExit2 = NULL;
QString Message::Test = NULL;
QString Message::TryingToRun1 = NULL;
QString Message::TryingToRun2 = NULL;
QString Message::TryingToExpireScanCache = NULL;
QString Message::ScanCacheNotFound = NULL;

#define tscope "Const_Input::Message"
void Message::init()
{
    using namespace Const_Global::CommonString;

    InvalidCommand = trr(tscope, "Invalid command");
    TryingToPause = trr(tscope, "Trying to pause prefetch");
    PauseRequested = Tab + trr(tscope, "Pause has requested, good luck");
    TryingToResume = trr(tscope, "Trying to resume prefetch");
    TryingToExit1 = trr(tscope, "Trying to exit prefetch");
    TryingToExit2 = Tab + trr(tscope, "This can take a while in some case");
    Test = trr(tscope, "This function contain test code");
    TryingToRun1 = trr(tscope, "Trying to run program");
    TryingToRun2 = Tab;
    TryingToExpireScanCache = trr(tscope, "Trying to expire scan cache");
    ScanCacheNotFound = Tab + trr(tscope, "Scan cache not found, ignore");
}
void Message::tdummy()
{
    using namespace Const_Global::CommonString;

    InvalidCommand = tr("Invalid command");
    TryingToPause = tr("Trying to pause prefetch");
    PauseRequested = Tab + tr("Pause has requested, good luck");
    TryingToResume = tr("Trying to resume prefetch");
    TryingToExit1 = tr("Trying to exit prefetch");
    TryingToExit2 = Tab + tr("This can take a while in some case");
    Test = tr("This function contain test code");
    TryingToRun1 = tr("Trying to run program");
    TryingToRun2 = Tab;
    TryingToExpireScanCache = tr("Trying to expire scan cache");
    ScanCacheNotFound = Tab + tr("Scan cache not found, ignore");
}

QString Command_Level2::splitter = Const_Global::CommonString::Space;
const QString Command_Level2::run_withSplitter = Command_Level2::run + Command_Level2::splitter;
const QString Command_Level2::run_quiet_withSplitter = Command_Level2::run + Command_Level2::splitter;
