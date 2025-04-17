// Change Dispenser H file

#ifndef CHANGE_DISPENSER_H
#define CHANGE_DISPENSER_H

#include <vector>
#include "money/coin.h"
#include "event/event_manager.h"
#include "money/change_dispenser_io.h"
#include "money/change_drawer.h"
class ChangeDispenser {
    public:
        ChangeDispenser(EventManager* eventManager, ChangeDrawer* changeDrawer);
        void onGiveChange(EventData data);
        void onResetForNewTransaction();
    private:
        double total_change;
        void calculateChange(double totalInsertedValue);
        ChangeDispenserIO io;
        EventManager* eventManager;
        ChangeDrawer* changeDrawer;

        friend class ChangeDispenserIO;
};

#endif
