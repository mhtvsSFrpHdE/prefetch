#include "const_core.h"
#include "..\Setting\const_setting.h"
#include "..\Global\const_global.h"

using namespace Const_Global::CommonString;
const QString Const_Core::Message::CacheFound = Tab + "Cache found, restore file list";
const QString Const_Core::Message::RescanIntervalReached2 = Tab + "Cache will expire on next run.";

const QString Const_Cache::PathSplitter = Const_Setting::PathSplitter;
