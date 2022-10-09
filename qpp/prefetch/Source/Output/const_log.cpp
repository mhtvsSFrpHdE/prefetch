#include "const_log.h"
#include "..\Setting\const_setting.h"
#include "..\Global\const_global.h"
#include "..\Translate\translate_tool.h"
#include "..\Translate\translate_define.h"

QString Const_Log::PathSplitter = NULL;

QString Const_Log::Message::NewLine = NULL;
QString Const_Log::Message::Tab = NULL;

QString Const_Log::Message::LastKnownLocation_BEGIN = NULL;
QString Const_Log::Message::LastKnownLocation_END = NULL;
QString Const_Log::Message::LastKnownLocation_INLINE = NULL;
QString Const_Log::Message::LastKnownLocation_LOCK = NULL;
QString Const_Log::Message::LastKnownLocation_UNLOCK = NULL;
QString Const_Log::Message::File = NULL;
QString Const_Log::Message::Function = NULL;
QString Const_Log::Message::Line = NULL;

void Const_Log::Message::init()
{
    PathSplitter = Const_Setting::PathSplitter;

    NewLine = Const_Global::CommonString::NewLine;
    Tab = Const_Global::CommonString::Tab;

    LastKnownLocation_BEGIN = tr("LastKnownLocation BEGIN\n");
    LastKnownLocation_END = tr("LastKnownLocation END\n");
    LastKnownLocation_INLINE = tr("LastKnownLocation INLINE\n");
    LastKnownLocation_LOCK = tr("LastKnownLocation LOCK\n");
    LastKnownLocation_UNLOCK = tr("LastKnownLocation UNLOCK\n");
    File = Tab + tr("File: ");
    Function = Tab + tr("Function: ");
    Line = Tab + tr("Line: ");
}
