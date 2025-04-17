// Money Handler Test Driver cpp

#include <iostream>
#include "money/coin_slot.h" 
#include "event/event_manager.h"
#include "money/change_drawer.h"
#include "money/change_dispenser.h"

// g++ -Iheader source/money/coin_slot.cpp source/money/money_test_driver.cpp source/money/coin_slot_io.cpp source/money/coin.cpp source/money/collected_coin.cpp source/money/collected_coin_io.cpp source/money/coin_storage.cpp source/money/coin_storage_io.cpp source/money/change_drawer.cpp source/money/change_drawer_io.cpp source/money/change_dispenser.cpp source/money/change_dispenser_io.cpp source/event/event_manager.cpp -std=c++17 -o money_test

int main(){
    std::cout << "Money Test Driver" << std::endl;

    // TESTING COIN INSERTION
    EventManager eventManager;
    std::unordered_map<std::string, int> coin_storage{
        {"NICKEL", 15},
        {"DIME", 20},
        {"QUARTER", 12}
    };
    CollectedCoin collectedCoin(coin_storage, &eventManager);
    CoinSlot coinSlot(&eventManager, &collectedCoin, 1.00);
    // coinSlot.startCoinInsertion();

    
   // TESTING MONEY COLLECTION
   // collectedCoin.onCollectMoney();


   // TESTING CHANGE DRAWER AND CHANGE DISPENSER
    /*
   ChangeDrawer changeDrawer(&eventManager);
   ChangeDispenser changeDispenser(&eventManager, &changeDrawer);

   EventData data;
   data.inserted_amount = 2.00;
   data.beverage_cost = 1.05;

   std::cout << "\nCHANGE BEFORE" << std::endl;
   changeDrawer.displayChangeLevels();

   //changeDispenser.onGiveChange(data);

   std::cout << "\nCHANGE AFTER" << std::endl;
   changeDrawer.displayChangeLevels();
   */

   // TESTING CHANGE DRAWER CHANGE INSERTION MAIINTENANCE
   std::unordered_map<std::string, int> max_capacity{
    {"NICKEL", 30},
    {"DIME", 30},
    {"QUARTER", 30}
};
ChangeDrawer changeDrawer2(&eventManager, max_capacity);
changeDrawer2.displayChangeLevels();
changeDrawer2.onRefillChange();

    return 0;
}