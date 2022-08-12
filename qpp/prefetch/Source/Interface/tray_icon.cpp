#include <QMenu>
#include <QAction>

#include "..\Global\global.h"
#include "..\Output\stdout.h"

QSystemTrayIcon *TrayIcon::systemTrayIcon = NULL;

void TrayIcon::init()
{
    TrayIcon::systemTrayIcon = new QSystemTrayIcon(Global::qGuiApplication);

    QMenu *qMenu = new QMenu();

    QAction *pauseAction = new QAction("Pause", qMenu);
    connect(pauseAction, SIGNAL(triggered()), this, SLOT(action_pause()));
    qMenu->addAction(pauseAction);

    QAction *resumeAction = new QAction("Resume", qMenu);
    connect(resumeAction, SIGNAL(triggered()), this, SLOT(action_resume()));
    qMenu->addAction(resumeAction);

    systemTrayIcon->setContextMenu(qMenu);
}

void TrayIcon::start()
{
    TrayIcon::systemTrayIcon->setIcon(QIcon(":/qrc/Resource/icon/main/prefetch.png"));
    TrayIcon::systemTrayIcon->show();
}

void TrayIcon::action_pause()
{
    *StdOut::consoleOutput << "Click pause"
                           << endl;
    StdOut::consoleOutput->flush();
}
void TrayIcon::action_resume()
{
     *StdOut::consoleOutput << "Click resume"
                           << endl;
    StdOut::consoleOutput->flush();
}
