#include <QProcess>

#include "start_process.h"

void StartProcess::startProcess(QString fileName)
{
    QProcess process;
    process.startDetached(fileName);
}
