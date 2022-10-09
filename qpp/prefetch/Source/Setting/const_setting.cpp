#include "const_setting.h"
#include "..\Global\const_global.h"

using namespace Const_Global::CommonString;

QString Const_Setting::PathSplitter = NULL;
QString Const_Setting::StringListSplitter = NULL;

QString Const_Setting::Instance_Font_Value::Default = NULL;

QString Const_Setting::MainWindow_Position_Value::Default = NULL;

void Const_Setting::init()
{
    PathSplitter = QtPathSplitter;
    StringListSplitter = StringListSplitterType1;

    Instance_Font_Value::Default = SettingDefaultValueType1;

    MainWindow_Position_Value::Default = SettingDefaultValueType1;
}
