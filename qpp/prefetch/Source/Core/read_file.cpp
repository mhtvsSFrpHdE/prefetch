#include <QThread>
#include <QString>

#include "core.h"
#include "..\Setting\const_setting.h"

SleepThread *Core::sleepThreadAddress = NULL;
int Core::count_start_scanFolder = 0;
QList<QRunnable *> Core::readThreadQueue = QList<QRunnable *>();
QThreadPool *Core::readThreadPool = new QThreadPool();
int Core::count_taskComplete = 0;

using namespace Const_Setting::Value::Thread;

// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, QThread::Priority> Core::priorityMap(
    std::map<QString, QThread::Priority>{
        {ReadThreadPriority::IdlePriority, QThread::IdlePriority},
        {ReadThreadPriority::LowestPriority, QThread::LowestPriority},
        {ReadThreadPriority::LowPriority, QThread::LowPriority},
        {ReadThreadPriority::NormalPriority, QThread::NormalPriority},
        {ReadThreadPriority::HighPriority, QThread::HighPriority},
        {ReadThreadPriority::HighestPriority, QThread::HighestPriority},
        {ReadThreadPriority::TimeCriticalPriority, QThread::TimeCriticalPriority},
        {ReadThreadPriority::InheritPriority, QThread::InheritPriority}});
