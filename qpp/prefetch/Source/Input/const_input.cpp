#include "const_input.h"
#include "..\Global\const_global.h"

using namespace Const_Input;
using namespace Const_Global;

const QString Message::PauseRequested = CommonString::Tab + "Pause has requested, good luck";
const QString Message::TryingToExit2 = CommonString::Tab + "This can take a while in some case";
const QString Message::TryingToRun2 = CommonString::Tab;
const QString Message::ScanCacheNotFound = CommonString::Tab + "Scan cache not found, ignore";

const QString Command_Level2::splitter = CommonString::Space;
const QString Command_Level2::run_withSplitter = Command_Level2::run + Command_Level2::splitter;
const QString Command_Level2::run_quiet_withSplitter = Command_Level2::run + Command_Level2::splitter;
