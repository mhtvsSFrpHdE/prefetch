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

public slots:
    void print_slot(QString textToPrint);
    void sendCommand_slot();
    void scrollBarToBottom_slot();

signals:
    void print_signal(QString textToPrint);

private:
    Ui::MainWindow *ui;

    // Skip 2nd exit request if fired multiple times
    static bool exitRequested;

    // Handle application close event
    void closeEvent(QCloseEvent *closeEventAddress) override;
};

#endif // MAINWINDOW_H
