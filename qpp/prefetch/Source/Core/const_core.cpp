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

void Const_Core::Message::init()
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
}

QString Const_Cache::PathSplitter = Const_Setting::PathSplitter;
