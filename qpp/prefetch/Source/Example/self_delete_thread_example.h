#ifndef SlefDeleteThreadExample_h
#define SlefDeleteThreadExample_h

#include <QObject>
#include <QThread>

// Simple thread manager
// Take a QThread object, delete it on it's finished signal
//     then delete thread manager itself
class SlefDeleteThreadExample : public QObject
{
    Q_OBJECT
public:
    SlefDeleteThreadExample(QThread *thread)
    {
        SlefDeleteThreadExample::thread = thread;
        connect(thread, SIGNAL(finished()), this, SLOT(deleteThis()));
    }
public slots:
    void deleteThis()
    {
        delete thread;
        deleteLater();
    }

private:
    QThread *thread = NULL;
};

#endif
