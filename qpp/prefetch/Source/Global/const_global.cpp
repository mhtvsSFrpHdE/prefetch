#include "const_global.h"
#include "..\Translate\translate_tool.h"
#include "..\Translate\translate_define.h"

QString Const_Global::CommonString::EmptyString = NULL;
QString Const_Global::CommonString::Space = NULL;
QString Const_Global::CommonString::NewLine = NULL;
QString Const_Global::CommonString::Tab = NULL;
QString Const_Global::CommonString::Quote = NULL;
QString Const_Global::CommonString::QtPathSplitter = NULL;
QString Const_Global::CommonString::SettingDefaultValueType1 = NULL;
QString Const_Global::CommonString::StringListSplitterType1 = NULL;

void Const_Global::CommonString::init()
{
    EmptyString = tr("");
    Space = tr(" ");
    NewLine = tr("\n");
    Tab = tr("    ");
    Quote = tr("\"");
    QtPathSplitter = tr("/");
    SettingDefaultValueType1 = tr("<default>");
    StringListSplitterType1 = tr(",");
}
