#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Implement Output::StdOut
    //
    // Note: Call UI element in main thread or will get these on console
    // ```
    // QObject::connect: Cannot queue arguments of type 'QTextBlock'
    // (Make sure 'QTextBlock' is registered using qRegisterMetaType().)
    // QObject::connect: Cannot queue arguments of type 'QTextCursor'
    // (Make sure 'QTextCursor' is registered using qRegisterMetaType().)
    // ```
    // https://stackoverflow.com/questions/2104779/qobject-qplaintextedit-multithreading-issues
    void StdOut_print(QString textToPrint);
    void StdOut_printLine(QString textToPrint);

    // If start with window set to false, skip show MainWindow
    void start();

public slots:
    void print_slot(QString textToPrint);
    void sendCommand_slot();
    void scrollBarToBottom_slot();

    // If I do `window.show()`, then a nonsense QTimer is required to do `window.setWindowState()`
    //     It seems the current function must be returned, and keep executing code from somewhere else
    //     The bug should be related to Qt internal event system and I can't do much things about it
    //
    // > As a special case, a QTimer with a timeout of 0 will time out as soon as all the events in the window system's event queue have been processed.
    // http://qt-project.org/doc/qt-4.8/qtimer.html#details
    // https://stackoverflow.com/questions/3332257/how-do-i-properly-implement-a-minimize-to-tray-function-in-qt
    void minimized_slot();
    void restored_slot();

signals:
    void print_signal(QString textToPrint);

private:
    Ui::MainWindow *ui;

    // Skip 2nd exit request if fired multiple times
    bool exitRequested = false;

    bool startToTray;
    bool minimizeToTray;
    int printOffset;

    // Handle application close event
    void closeEvent(QCloseEvent *closeEventAddress) override;

    // Handle application minimize event
    void changeEvent(QEvent *event) override;
};

#endif // MAINWINDOW_H
