#include <QTime>

#include "time.h"
#include "../const_core.h"

#define cm Const_Core::Message

QString Core_Time::timeConsumed(qint64 miliseconds)
{
    // 28
    auto msInSec = QString::number(miliseconds / 1000);

    // .105
    auto result = QTime()
                      .addMSecs(miliseconds)
                      .toString(cm::CodeExecuteTimeFormatter);

    // .105 -> .10
    result.chop(1);

    // .10 -> 28.10
    result = msInSec + result;

    return result;
}
