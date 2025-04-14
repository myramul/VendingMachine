#ifndef CHANGE_DISPENSER_H
#define CHANGE_DISPENSER_H

#include <vector>
#include "coin.h"
#include "event_manager.h"
#include "change_dispenser_io.h"
#include "change_drawer.h"
class ChangeDispenser {
    public:
        ChangeDispenser(EventManager* eventManager);
        void onGiveChange(EventData data);
    private:
        std::vector<Coin> change;
        double total_change;
        void calculateChange(double totalInsertedValue);
        ChangeDispenserIO io;
        EventManager* eventManager;
        ChangeDrawer* changeDrawer;
};

#endif