#ifndef Read_Thread_h
#define Read_Thread_h

#include <QRunnable>
#include <QString>
#include <QMutex>
#include <QStringList>
#include <QMap>
#include <QFile>

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
    static bool stop;

    // Unless available, do not start read loop
    static QMutex *stopMutex;

    // A thread that report it can be delete goes here
    static QList<QRunnable *> pendingDeleteThread;
    // QList only support one at same time
    //     Or the list can lose some change
    static QMutex pendingDeleteThreadMutex;
    static void lockPendingDeleteThread();
    static void unlockPendingDeleteThread();

    void run() override;

    // Save file path
    QString filePath;

    // Assume each file is created from cache first
    // Modify to false if created from search
    bool skipSearch;

    // Any init code
    static void init();

    // Redirect buffer function at runtime
    static void (*newSharedReadBuffer_action)();
    static void (*deleteSharedReadBuffer_action)();

private:
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

    // Redirect read file function at runtime
    static void (*run_read_action)(QFile *);
    static void run_read_WithBuffer(QFile *file);
    static void run_read_Directly(QFile *file);

    // Reduce waste, try read different file bytes to same RAM space
    // This variable should never be read from elsewhere:
    //     - Write only, no read
    //     - Parallel write without lock, so data is corrupted definitely
    //     - Use as /dev/null, discard what I don't want
    static char *sharedReadBuffer;
    // Size of sharedReadBuffer
    //     ReadBufferSize * 1024 * 1024
    static int sharedReadBufferSize;

    // If buffer is enabled, allocate RAM
    // Note: New twice = Memory leak
    static void newSharedReadBuffer_WithBuffer();
    static void newSharedReadBuffer_Directly();

    // Note: Delete twice is undefined behavior
    static void deleteSharedReadBuffer_WithBuffer();
    static void deleteSharedReadBuffer_Directly();
};

#endif
