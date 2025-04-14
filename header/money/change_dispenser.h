#ifndef CHANGE_DISPENSER_H
#define CHANGE_DISPENSER_H

#include <vector>
#include "coin.h"
#include "event_manager.h"
#include "change_dispenser_io.h"
class ChangeDispenser {
    public:
        void onGiveChange(EventData data);
    private:
        std::vector<Coin> change;
        double total_change;
        void calculateChange();
        ChangeDispenserIO io;
};

#endif