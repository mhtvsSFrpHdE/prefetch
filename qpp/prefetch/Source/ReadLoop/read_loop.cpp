#include <QThread>
#include <QString>

#include "read_loop.h"
#include "../Setting/const_setting.h"

SleepThread *ReadLoop::sleepThreadAddress = NULL;
int ReadLoop::count_start_scanFolder = 0;
QList<QRunnable *> ReadLoop::readThreadQueue = QList<QRunnable *>();
QThreadPool *ReadLoop::readThreadPool = new QThreadPool();
int ReadLoop::count_taskComplete = 0;

using namespace Const_Setting::Value::Thread;

// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, QThread::Priority> ReadLoop::priorityMap(
    std::map<QString, QThread::Priority>{
        {ReadThreadPriority::IdlePriority, QThread::IdlePriority},
        {ReadThreadPriority::LowestPriority, QThread::LowestPriority},
        {ReadThreadPriority::LowPriority, QThread::LowPriority},
        {ReadThreadPriority::NormalPriority, QThread::NormalPriority},
        {ReadThreadPriority::HighPriority, QThread::HighPriority},
        {ReadThreadPriority::HighestPriority, QThread::HighestPriority},
        {ReadThreadPriority::TimeCriticalPriority, QThread::TimeCriticalPriority},
        {ReadThreadPriority::InheritPriority, QThread::InheritPriority}});
