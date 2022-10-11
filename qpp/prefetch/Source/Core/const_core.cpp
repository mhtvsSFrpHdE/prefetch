#include "const_core.h"
#include "..\Setting\const_setting.h"
#include "..\Global\const_global.h"
#include "..\Translate\translate_tool.h"
#include "..\Translate\translate_define.h"

QString Const_Core::Message::ScanFolder = NULL;
QString Const_Core::Message::CacheFound = NULL;
QString Const_Core::Message::Prefetching = NULL;
QString Const_Core::Message::Idle_Time = NULL;
QString Const_Core::Message::Idle_Sec = NULL;
QString Const_Core::Message::ScanFolder_Time = NULL;
QString Const_Core::Message::ScanFolder_Sec = NULL;
QString Const_Core::Message::CodeExecuteTimeFormatter = NULL;
QString Const_Core::Message::RescanIntervalReached1 = NULL;
QString Const_Core::Message::RescanIntervalReached2 = NULL;

QString Const_Core::Message::RunStartupItems = NULL;

#define tscope "Const_Core::Message"
void Const_Core::Message::init()
{
    using namespace Const_Global::CommonString;

    ScanFolder = trr(tscope, "Scan folder...");
    CacheFound = Tab + trr(tscope, "Cache found, restore file list");
    Prefetching = trr(tscope, "Prefetching...");
    Idle_Time = Tab + trr(tscope, "Idle, Time: ");
    Idle_Sec = trr(tscope, " Sec");
    ScanFolder_Time = Tab + trr(tscope, "Scan complete, Time: ");
    ScanFolder_Sec = Const_Core::Message::Idle_Sec;
    CodeExecuteTimeFormatter = trr(tscope, "ss.zzz");
    RescanIntervalReached1 = trr(tscope, "Rescan interval reached.");
    RescanIntervalReached2 = Tab + trr(tscope, "Cache will expire on next run.");
    RunStartupItems = trr(tscope, "Cache will expire on next run.");
}

QString Const_Cache::PathSplitter = Const_Setting::PathSplitter;

void Const_Core::Message::tdummy()
{
    using namespace Const_Global::CommonString;

    ScanFolder = tr("Scan folder...");
    CacheFound = Tab + tr("Cache found, restore file list");
    Prefetching = tr("Prefetching...");
    Idle_Time = Tab + tr("Idle, Time: ");
    Idle_Sec = tr(" Sec");
    ScanFolder_Time = Tab + tr("Scan complete, Time: ");
    ScanFolder_Sec = Const_Core::Message::Idle_Sec;
    CodeExecuteTimeFormatter = tr("ss.zzz");
    RescanIntervalReached1 = tr("Rescan interval reached.");
    RescanIntervalReached2 = Tab + tr("Cache will expire on next run.");
    RunStartupItems = tr("Cache will expire on next run.");
}
