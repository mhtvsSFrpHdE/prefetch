#include "const_input_tdummy.cpp"

#include "..\Global\const_global.h"

using namespace Const_Input;
using namespace Const_Global::CommonString;

QString Message::InvalidCommand = DEFINE_InvalidCommand;
QString Message::TryingToPause = DEFINE_TryingToPause;
QString Message::PauseRequested = Tab + DEFINE_PauseRequested;
QString Message::TryingToResume = DEFINE_TryingToResume;
QString Message::TryingToExit1 = DEFINE_TryingToExit1;
QString Message::TryingToExit2 = Tab + DEFINE_TryingToExit2;
QString Message::Test = DEFINE_Test;
QString Message::TryingToRun1 = DEFINE_TryingToRun1;
QString Message::TryingToRun2 = Tab;
QString Message::TryingToExpireScanCache = DEFINE_TryingToExpireScanCache;
QString Message::ScanCacheNotFound = Tab + DEFINE_ScanCacheNotFound;
QString Message::TryingToLoadTranslate = DEFINE_TryingToLoadTranslate;
QString Message::FailedToLoadTranslate = DEFINE_FailedToLoadTranslate;
QString Message::TranslateFileLoaded = DEFINE_TranslateFileLoaded;

void Message::init()
{
    InvalidCommand = trr(tscope, DEFINE_InvalidCommand);
    TryingToPause = trr(tscope, DEFINE_TryingToPause);
    PauseRequested = Tab + trr(tscope, DEFINE_PauseRequested);
    TryingToResume = trr(tscope, DEFINE_TryingToResume);
    TryingToExit1 = trr(tscope, DEFINE_TryingToExit1);
    TryingToExit2 = Tab + trr(tscope, DEFINE_TryingToExit2);
    Test = trr(tscope, DEFINE_Test);
    TryingToRun1 = trr(tscope, DEFINE_TryingToRun1);
    TryingToExpireScanCache = trr(tscope, DEFINE_TryingToExpireScanCache);
    ScanCacheNotFound = Tab + trr(tscope, DEFINE_ScanCacheNotFound);
    TryingToLoadTranslate = trr(tscope, DEFINE_TryingToLoadTranslate);
    FailedToLoadTranslate = trr(tscope, DEFINE_FailedToLoadTranslate);
    TranslateFileLoaded = trr(tscope, DEFINE_TranslateFileLoaded);
}

QString Command_Level2::splitter = Const_Global::CommonString::Space;
const QString Command_Level2::run_withSplitter = Command_Level2::run + Command_Level2::splitter;
const QString Command_Level2::run_quiet_withSplitter = Command_Level2::run + Command_Level2::splitter;
