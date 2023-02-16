#include <QProcess>

#include "start_process.h"

void Core_StartProcess::startProcess(QString fileName)
{
    QProcess process;
    process.startDetached(fileName);
    process.waitForStarted();
}

QString Core_StartProcess::startProcessGetStdOut(QString fileName)
{
    QProcess process;
    process.start(fileName);
    process.waitForFinished();

    QString result = process.readAllStandardOutput();
    return result;
}
