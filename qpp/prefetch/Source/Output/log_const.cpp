#include "log_const.h"
#include "..\Setting\const_setting.h"
#include "..\Global\const_global.h"

const QString Const_Log::PathSplitter = Const_Setting::PathSplitter;

const QString Const_Log::Message::NewLine = Const_Global::CommonString::NewLine;
const QString Const_Log::Message::Tab = Const_Global::CommonString::Tab;
const QString Const_Log::Message::File = Tab + "File: ";
const QString Const_Log::Message::Function = Tab + "Function: ";
const QString Const_Log::Message::Line = Tab + "Line: ";
