#include <QThread>
#include <QMap>

class LoopThread : public QThread
{
    Q_OBJECT
public:
    LoopThread();

    void run() override;

public slots:
    // Input from remote
    void receiveText(QString input);

private:
    // Convert stdin command to function pointer
    static QMap<QString, void (*)()> commandMap;
};
