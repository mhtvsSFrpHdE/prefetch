#include <QThread>
#include <QString>

#include "read_file.h"
#include "..\..\Setting\const_setting.h"

SleepThread *ReadFile::sleepThreadAddress = new SleepThread();
int ReadFile::count_start_scanFolder = 0;
QList<QRunnable *> ReadFile::readThreadQueue = QList<QRunnable *>();
QThreadPool *ReadFile::readThreadPool = new QThreadPool();
int ReadFile::count_taskComplete = 0;

using namespace Const_Setting;
// Cool stuff: https://stackoverflow.com/questions/8157625/how-do-i-populate-values-of-a-static-qmap-in-c-qt
// Use initializer list and one of the QMap constructor
QMap<QString, QThread::Priority> ReadFile::priorityMap(
    std::map<QString, QThread::Priority>{
        {ReadThreadPriority_Value::IdlePriority, QThread::IdlePriority},
        {ReadThreadPriority_Value::LowestPriority, QThread::LowestPriority},
        {ReadThreadPriority_Value::LowPriority, QThread::LowPriority},
        {ReadThreadPriority_Value::NormalPriority, QThread::NormalPriority},
        {ReadThreadPriority_Value::HighPriority, QThread::HighPriority},
        {ReadThreadPriority_Value::HighestPriority, QThread::HighestPriority},
        {ReadThreadPriority_Value::TimeCriticalPriority, QThread::TimeCriticalPriority},
        {ReadThreadPriority_Value::InheritPriority, QThread::InheritPriority}});
