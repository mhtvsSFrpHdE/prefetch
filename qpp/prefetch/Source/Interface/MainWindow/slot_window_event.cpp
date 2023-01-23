#include <QTimer>

#include "mainwindow.h"

void MainWindow::minimized_slot()
{
    // Check minimize to tray enabled
    if (minimizeToTray == false)
    {
        // No action on false
        return;
    }

    // Hide (minimize to tray)
    QTimer::singleShot(0, this, SLOT(hide()));
}

void MainWindow::restored_slot()
{
    // Restore and bring to front if minimized before hide
    setWindowState(Qt::WindowState::WindowActive);

    updateScrollBar_slot();
}
