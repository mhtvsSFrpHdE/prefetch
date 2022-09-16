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
    void StdOut_print(QString textToPrint);
    void StdOut_printLine(QString textToPrint);
    void StdOut_flush();

    // If start with window set to false, skip show MainWindow
    void start();

    // https://www.qtcentre.org/threads/63281-Reading-last-lines-from-QTextEdit-Document
    // Says I need read all line, split by `\n` to array, and array[array.length-1]
    // I rather do a cache here
    QString lastKnownLine;

public slots:
    void print_slot(QString textToPrint);
    void sendCommand_slot();
    void scrollBarToBottom_slot();
    void updateScrollBar_slot();
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

    // Distinguish print and print line
    bool lastKnownLineCommitted = true;

    // Handle application close event
    void closeEvent(QCloseEvent *closeEventAddress) override;

    // Handle application minimize event
    void changeEvent(QEvent *changeEventAddress) override;
};

#endif // MAINWINDOW_H
