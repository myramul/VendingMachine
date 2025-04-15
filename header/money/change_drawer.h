// CHANGE_DRAWER.H

#ifndef CHANGE_DRAWER_H
#define CHANGE_DRAWER_H
#include "money/coin_storage.h"
#include "money/change_drawer_io.h"
#include "event/event_manager.h"

class ChangeDrawer : public CoinStorage{
    public:
        ChangeDrawer(EventManager* eventManager, std::unordered_map<std::string, int> max_capacity);
        ChangeDrawer(EventManager* eventManager);
        void onRefillChange();
        double getTotalChange();
        void refill_slot(std::string name, int quantity);
        void displayChangeLevels();
    private:
        std::unordered_map<std::string, int> max_capacity_slot = {
            {"NICKEL", 30},
            {"DIME", 30},
            {"QUARTER", 30}
        };
        ChangeDrawerIO io;
        EventManager* eventManager;
};

#endif