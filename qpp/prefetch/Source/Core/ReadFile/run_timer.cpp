#include <QTime>

#include "run_timer.h"
#include "..\const_core.h"

QString Run_Timer::timeConsumed(qint64 miliseconds)
{
    using namespace Const_Core::Message;

    auto result = QTime()
                      .addMSecs(miliseconds)
                      .toString(CodeExecuteTimeFormatter);
    result.chop(1);

    return result;
}
