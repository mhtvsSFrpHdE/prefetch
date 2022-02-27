#include <QDir>

#include "setting.h"

QSettings Setting::setting(QDir::currentPath() + "/prefetch.ini", QSettings::IniFormat);

void Setting::init(){
    QStringList keys = setting.childKeys();
}