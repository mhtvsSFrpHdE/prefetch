#include "const_read_loop_tdummy.cpp"

#include "../Setting/const_setting.h"
#include "../Global/const_global.h"

using namespace Const_Global::CommonString;

QString Const_ReadLoop::Message::ScanFolder = DEFINE_ScanFolder;
QString Const_ReadLoop::Message::CacheFound = Tab + DEFINE_CacheFound;
QString Const_ReadLoop::Message::Prefetching = DEFINE_Prefetching;
QString Const_ReadLoop::Message::Idle_Time = Tab + DEFINE_Idle_Time;
QString Const_ReadLoop::Message::Idle_Sec = DEFINE_Idle_Sec;
QString Const_ReadLoop::Message::ScanFolder_Time = Tab + DEFINE_ScanFolder_Time;
QString Const_ReadLoop::Message::ScanFolder_Sec = Idle_Sec;
QString Const_ReadLoop::Message::CodeExecuteTimeFormatter = DEFINE_CodeExecuteTimeFormatter;
QString Const_ReadLoop::Message::RescanIntervalReached1 = DEFINE_RescanIntervalReached1;
QString Const_ReadLoop::Message::RescanIntervalReached2 = Tab + DEFINE_RescanIntervalReached2;

QString Const_ReadLoop::Message::RunStartupItems = DEFINE_RunStartupItems;

QString Const_ReadLoop::Message::SkipProcessDetected = DEFINE_SkipProcessDetected;

void Const_ReadLoop::Message::init()
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

    SkipProcessDetected = Tab + trr(tscope, DEFINE_SkipProcessDetected);
}

QString Const_Cache::PathSplitter()
{
    return Const_Setting::PathSplitter;
}
