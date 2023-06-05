#include <QProcess>

#include "start_process.h"

void ReadLoop_StartProcess::startProcess(QString fileName)
{
    QProcess process;
    process.startDetached(fileName);
}

QString ReadLoop_StartProcess::startProcessGetStdOut(QString fileName)
{
    QProcess process;
    process.start(fileName);
    process.waitForFinished();

    QString result = process.readAllStandardOutput();
    return result;
}
