#include <QThread>
#include <QString>

#include "read_file.h"
#include "..\..\Setting\const_setting.h"

SleepThread *ReadFile::sleepThreadAddress = NULL;
int ReadFile::count_start_scanFolder = 0;
QList<QRunnable *> ReadFile::readThreadQueue = QList<QRunnable *>();
QThreadPool *ReadFile::readThreadPool = new QThreadPool();
int ReadFile::count_taskComplete = 0;

using namespace Const_Setting::Value::Thread;
// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, QThread::Priority> ReadFile::priorityMap(
    std::map<QString, QThread::Priority>{
        {ReadThreadPriority::IdlePriority, QThread::IdlePriority},
        {ReadThreadPriority::LowestPriority, QThread::LowestPriority},
        {ReadThreadPriority::LowPriority, QThread::LowPriority},
        {ReadThreadPriority::NormalPriority, QThread::NormalPriority},
        {ReadThreadPriority::HighPriority, QThread::HighPriority},
        {ReadThreadPriority::HighestPriority, QThread::HighestPriority},
        {ReadThreadPriority::TimeCriticalPriority, QThread::TimeCriticalPriority},
        {ReadThreadPriority::InheritPriority, QThread::InheritPriority}});
