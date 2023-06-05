#include <QTime>

#include "time.h"
#include "../const_read_loop.h"

#define cm Const_ReadLoop::Message

QString ReadLoop_Time::timeConsumed(qint64 miliseconds)
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
