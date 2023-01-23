#ifndef Function_Pointer_In_Signal_Slot_h
#define Function_Pointer_In_Signal_Slot_h

#include <QMetaType>

// See "function_pointer_in_signal_slot.h" for more details
typedef void (*mocFunctionPointer)();

// Qt component `moc_` does not support function pointer in signals/slots declare
// Code example provided in `HACK.md`
//
// Use typedef to spoof `moc_` parser, let it to think `void` does not repeat twice
// Then use `qRegisterMetaType` to tell Qt this new custom type available for connect
// This class so called MocFunctionPointer
//
// A pointer to class member function can't pass diretly as a "ordinary" function pointer without class
// For example:
//     `&MainWindow::` is not compatible with `void (*callback)()`
// These class function need to be wrapped by a function not in a class:
//     void sendCommand_restore_toOrdinary()
//     {
//         Global::qMainWindow->sendCommand_restore();
//     }
//     ...
//     emit callbackOnUiThread_signal(&sendCommand_restore_toOrdinary);
//
// https://stackoverflow.com/questions/27001844/why-doesnt-this-code-with-a-function-pointers-compile
// https://forum.qt.io/topic/78818/make-sure-mat-is-registered-using-qregistermetatype-error
// https://doc.qt.io/archives/qt-4.8/qmetatype.html
class MocFunctionPointer
{
public:
    // Any init code
    static void init()
    {
        qRegisterMetaType<mocFunctionPointer>("mocFunctionPointer");
    }
};

#endif
