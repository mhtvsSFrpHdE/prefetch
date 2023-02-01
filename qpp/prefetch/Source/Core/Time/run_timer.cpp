#include <QTime>

#include "run_timer.h"
#include "..\const_core.h"

QString Run_Timer::timeConsumed(qint64 miliseconds)
{
    using namespace Const_Core::Message;

    // 28
    auto msInSec = QString::number(miliseconds / 1000);

    // .105
    auto result = QTime()
                      .addMSecs(miliseconds)
                      .toString(CodeExecuteTimeFormatter);

    // .105 -> .10
    result.chop(1);

    // .10 -> 28.10
    result = msInSec + result;

    return result;
}
