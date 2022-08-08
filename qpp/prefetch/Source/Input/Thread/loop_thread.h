#include <QThread>
#include <QMap>

class LoopThread : public QThread
{
    Q_OBJECT
public:
    LoopThread();

    void run() override;

private:
    // Convert stdin command to function pointer
    static QMap<QString, void (*)()> commandMap;
};
