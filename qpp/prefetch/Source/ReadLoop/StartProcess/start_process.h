#include <QString>

class ReadLoop_StartProcess
{
public:
    // Cool stuff
    // Use startDetached to avoid print to console
    // QProcess: Destroyed while process is still running.
    static void startProcess(QString fileName);

    // Block until stdout returned
    static QString startProcessGetStdOut(QString fileName);
};
