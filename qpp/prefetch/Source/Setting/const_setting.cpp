#include "const_setting.h"
#include "../Global/const_global.h"

using namespace Const_Global::CommonString;

QString Const_Setting::PathSplitter = QtPathSplitter;
QString Const_Setting::StringListSplitter = StringListSplitterType1;

QString Const_Setting::Value::Instance::Font::Default = DefaultValueType1;
QString Const_Setting::Value::Instance::Language::Default = DefaultValueType1;
QString Const_Setting::Value::Instance::TranslateFolder::Default = DefaultValueType1;

QString Const_Setting::Value::MainWindow::Position::Default = DefaultValueType1;

QString Const_Setting::Exception::FailedToOpenFile_UI = IncompatibleConfigVersion_UI;
