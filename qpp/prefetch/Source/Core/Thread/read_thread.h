#include <QRunnable>
#include <QString>
#include <QMutex>
#include <QStringList>

class ReadThread : public QRunnable
{
public:
    ReadThread(QString filePath);

    // Everytime creating a new instance, call set setAutoDelete
    // Default: true
    static bool autoDeletePreset;

    // File under exclude folders will not prefetch
    static QStringList excludeFolders;

    void run();

private:
    // Save file path
    QString filePath;

    // Every file need do search to confirm if excluded
    // Shall not search again if thread can run multiple times
    //
    // There are other reasons can change this varialbe too
    bool skip;

    // Prevent access stdio at same time
    static QMutex printLock;
};