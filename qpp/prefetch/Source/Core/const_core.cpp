#include "const_core_tdummy.cpp"

#include "..\Setting\const_setting.h"
#include "..\Global\const_global.h"

using namespace Const_Global::CommonString;

QString Const_Core::Message::ScanFolder = DEFINE_ScanFolder;
QString Const_Core::Message::CacheFound = Tab + DEFINE_CacheFound;
QString Const_Core::Message::Prefetching = DEFINE_Prefetching;
QString Const_Core::Message::Idle_Time = Tab + DEFINE_Idle_Time;
QString Const_Core::Message::Idle_Sec = DEFINE_Idle_Sec;
QString Const_Core::Message::ScanFolder_Time = Tab + DEFINE_ScanFolder_Time;
QString Const_Core::Message::ScanFolder_Sec = Idle_Sec;
QString Const_Core::Message::CodeExecuteTimeFormatter = DEFINE_CodeExecuteTimeFormatter;
QString Const_Core::Message::RescanIntervalReached1 = DEFINE_RescanIntervalReached1;
QString Const_Core::Message::RescanIntervalReached2 = Tab + DEFINE_RescanIntervalReached2;

QString Const_Core::Message::RunStartupItems = DEFINE_RunStartupItems;

void Const_Core::Message::init()
{
    ScanFolder = trr(tscope, DEFINE_ScanFolder);
    CacheFound = Tab + trr(tscope, DEFINE_CacheFound);
    Prefetching = trr(tscope, DEFINE_Prefetching);
    Idle_Time = Tab + trr(tscope, DEFINE_Idle_Time);
    Idle_Sec = trr(tscope, DEFINE_Idle_Sec);
    ScanFolder_Time = Tab + trr(tscope, DEFINE_ScanFolder_Time);
    ScanFolder_Sec = Idle_Sec;
    CodeExecuteTimeFormatter = trr(tscope, DEFINE_CodeExecuteTimeFormatter);
    RescanIntervalReached1 = trr(tscope, DEFINE_RescanIntervalReached1);
    RescanIntervalReached2 = Tab + trr(tscope, DEFINE_RescanIntervalReached2);

    RunStartupItems = trr(tscope, DEFINE_RunStartupItems);
}

QString Const_Cache::PathSplitter = Const_Setting::PathSplitter;
