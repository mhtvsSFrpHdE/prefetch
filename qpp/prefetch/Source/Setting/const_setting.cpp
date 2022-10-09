#include "const_setting.h"
#include "..\Global\const_global.h"

using namespace Const_Global::CommonString;

QString Const_Setting::PathSplitter = NULL;
QString Const_Setting::StringListSplitter = NULL;

QString Const_Setting::Font_Value::Default = NULL;

QString Const_Setting::Position_Value::Default = NULL;

QString Const_Setting::Size_Value::Splitter = NULL;

void Const_Setting::init()
{
    PathSplitter = QtPathSplitter;
    StringListSplitter = StringListSplitterType1;

    Font_Value::Default = SettingDefaultValueType1;

    Position_Value::Default = SettingDefaultValueType1;

    Size_Value::Splitter = StringListSplitter;
}
