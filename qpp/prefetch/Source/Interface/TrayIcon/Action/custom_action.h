#include <QAction>
#include <QString>

typedef void (*ParameterSlot)(void *);

// QAction, connect void signal to parameter slot
// Designed for custom tray menu at the beginning, beware
class CustomAction : public QAction
{
    Q_OBJECT

public:
    CustomAction(const QString &text, QObject *parent) : QAction(text, parent){};

    // Pointer to function is different than pointer to member function
    //
    // Must do `ParameterSlot(&FullNamespace::functionName)` instead of `&functionName`:
    //     Without namespace, another ISO C++ error will appear
    //     Without `ParameterSlot(something)` the one look like class constructor, can't pass non static function as parameter
    // https://stackoverflow.com/questions/45331989/c-pointer-to-non-static-member-functions
    void init(void *freeStore, ParameterSlot triggered);

    // The one pass from init
    // This class don't care about variable type:
    //     depending on init, it can be ANYTHING
    void *freeStore;
    ParameterSlot triggeredSlotStore;

public slots:
    void triggered_slot();
};
