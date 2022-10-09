#include "const_input.h"
#include "..\Global\const_global.h"

using namespace Const_Input;
using namespace Const_Global;

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

void Message::init()
{
    InvalidCommand = "Invalid command";
    TryingToPause = "Trying to pause prefetch";
    PauseRequested = CommonString::Tab + "Pause has requested, good luck";
    TryingToResume = "Trying to resume prefetch";
    TryingToExit1 = "Trying to exit prefetch";
    TryingToExit2 = CommonString::Tab + "This can take a while in some case";
    Test = "This function contain test code";
    TryingToRun1 = "Trying to run program";
    TryingToRun2 = CommonString::Tab;
    TryingToExpireScanCache = "Trying to expire scan cache";
    ScanCacheNotFound = CommonString::Tab + "Scan cache not found, ignore";
}

QString Command_Level2::splitter = NULL;
const QString Command_Level2::run_withSplitter = Command_Level2::run + Command_Level2::splitter;
const QString Command_Level2::run_quiet_withSplitter = Command_Level2::run + Command_Level2::splitter;

void Command_Level2::init()
{
    splitter = CommonString::Space;
}
