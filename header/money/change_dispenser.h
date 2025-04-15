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
    private:
        std::vector<Coin> change;
        double total_change;
        void calculateChange(double totalInsertedValue);
        ChangeDispenserIO io;
        EventManager* eventManager;
        ChangeDrawer* changeDrawer;

        friend class ChangeDispenserIO;
};

#endif

/*
onGiveChange, it needs to calculate how much change is needed based on event data - inserted amount & beverage cost
and then check change drawer for potential coins to dispense
print out the total change returned and then the quantity of each coin
*/