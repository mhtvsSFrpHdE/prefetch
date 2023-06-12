#include <QMessageBox>

#include "exception_example.h"
#include "../Define/define_runtime.h"
#include "../Global/const_global.h"
#include "../Output/stdout.h"

void ExceptionExample::throwException(QString exceptionName, QString uiText)
{
    // StdOut
    StdOut::printLine(uiText);

    // Dialog
    bool noConsole = Define_Runtime::getConsoleEnabled() == false;
    if (noConsole)
    {
        QWidget dialogPartent;
        QMessageBox::critical(&dialogPartent, Const_Global::CommonString::EmptyString, uiText);
    }

    // Terminate execute
    throw std::runtime_error(exceptionName.toStdString());
}
