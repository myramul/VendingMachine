// CHANGE_DRAWER.H

#ifndef CHANGE_DRAWER_H
#define CHANGE_DRAWER_H
#include "coin_storage.h"
#include "change_drawer_io.h"

class ChangeDrawer : public CoinStorage{
    public:
        ChangeDrawer();
        void onRefllChange();
        double getTotalChange();
        void add_coin(std::string name, int quantity) override;
        void remove_coins(std::string name, int quantity) override;
        int get_coin_count(std::string name) override;
    private:
        void refill_slot(std::string name, int quantity);
        std::unordered_map<std::string, int> max_capacity_slot;
        ChangeDrawerIO io;
};

#endif