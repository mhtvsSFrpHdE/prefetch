#include <QProcess>

#include "start_process.h"

void StartProcess::startProcess(QString fileName)
{
    QProcess process;
    process.startDetached(fileName);
}

QString StartProcess::startProcessGetStdOut(QString fileName)
{
    QProcess process;
    process.start(fileName);
    process.waitForFinished();

    QString result = process.readAllStandardOutput();
    return result;
}
