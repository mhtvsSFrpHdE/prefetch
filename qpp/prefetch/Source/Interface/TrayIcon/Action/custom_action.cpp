#include "custom_action.h"

void CustomAction::init(void *freeStore, ParameterSlot triggered)
{
    this->freeStore = freeStore;
    this->triggeredSlotStore = triggered;
}

void CustomAction::triggered_slot()
{
    this->triggeredSlotStore(freeStore);
}
