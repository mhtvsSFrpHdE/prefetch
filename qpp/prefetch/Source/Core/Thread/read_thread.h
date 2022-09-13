#include <QRunnable>
#include <QString>
#include <QMutex>
#include <QStringList>
#include <QMap>

class ReadThread : public QRunnable
{
public:
    ReadThread(QString filePath);

    // Everytime creating a new instance, call set setAutoDelete
    // Default: true
    static bool autoDeletePreset;

    // File under exclude folders will not prefetch
    static QStringList excludeFolders;

    // File match search pattern will ignore exclude folders
    static QStringList priorityIncludePatterns;

    // Default is false, if set to true from other thread,
    //     each read will not happen but return immediately
    static bool pause;

    // A thread that report it can be delete goes here
    static QList<QRunnable *> pendingDeleteThread;
    // QList only support one at same time
    //     Or the list can lose some change
    static QMutex pendingDeleteThreadMutex;

    void run() override;

    // Save file path
    QString filePath;

    // Assume each file is created from cache first
    // Modify to false if created from search
    bool skipSearch;

private:
    // Prevent access stdio at same time
    static QMutex printLock;

    // Confirm file path is included or not
    // Return
    //     true: File path is included
    bool run_SearchInclude();

    // Confirm file path is excluded or not
    // Return
    //     true: File is excluded
    bool run_SearchExclude();

    // This file is excluded, delete read thread after first run
    void run_RequestDelete();

    // Prefetch file
    void run_read();
};
