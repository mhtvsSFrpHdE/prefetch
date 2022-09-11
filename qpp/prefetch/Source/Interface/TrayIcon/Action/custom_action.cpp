#include "custom_action.h"

void CustomAction::init(void *freeStore, ParameterSlot triggered)
{
    this->freeStore = freeStore;
    this->triggeredSlotStore = triggered;

    auto dbg_freeStore = (QString *)freeStore;
}

void CustomAction::triggered_slot()
{
    auto dbg_freeStore = (QString *)freeStore;

    this->triggeredSlotStore(freeStore);
}
