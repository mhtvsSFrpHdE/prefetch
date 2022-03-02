#include <QRunnable>
#include <QString>

class ReadThread : public QRunnable
{
public:
    ReadThread(QString filePath);

    void run();

private:
    QString filePath;
};