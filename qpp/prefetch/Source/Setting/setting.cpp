#include <QDir>
#include <QCoreApplication>

#include "setting.h"

QSettings *Setting::setting;

void Setting::init()
{
    // Read ini from exe stored folder
    setting = new QSettings(QCoreApplication::applicationDirPath() + "/prefetch.ini", QSettings::IniFormat);
}
