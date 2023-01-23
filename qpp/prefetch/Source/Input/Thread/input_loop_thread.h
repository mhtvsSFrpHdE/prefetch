#ifndef InputLoopThread_h
#define InputLoopThread_h

#include <QThread>

class InputLoopThread : public QThread
{
    Q_OBJECT
public:
    void run() override;

public slots:
    // Input from remote
    void receiveText(QString input);
};

#endif
