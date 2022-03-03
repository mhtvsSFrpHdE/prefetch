#include <QRunnable>
#include <QString>
#include <QMutex>

class ReadThread : public QRunnable
{
public:
    ReadThread(QString filePath);

    // Everytime creating a new instance, call set setAutoDelete
    // Default: true
    static bool autoDeletePreset;

    void run();

private:
    // Save file path
    QString filePath;

    // Prevent access stdio at same time
    static QMutex printLock;
};