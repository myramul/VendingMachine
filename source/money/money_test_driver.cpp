// Money Handler Test Driver cpp
// TO TUN THE FILE USING G++ Compiler:
// g++ -Iheader source/money/coin_slot.cpp source/money/money_test_driver.cpp source/money/coin_slot_io.cpp source/money/coin.cpp source/money/collected_coin.cpp source/money/collected_coin_io.cpp source/money/coin_storage.cpp source/money/coin_storage_io.cpp source/money/change_drawer.cpp source/money/change_drawer_io.cpp source/money/change_dispenser.cpp source/money/change_dispenser_io.cpp source/money/coin_return.cpp source/event/event_manager.cpp source/money/coin_return_io.cpp source/money/money_handler.cpp -std=c++17 -o money_test 

#include <iostream>
#include <cassert>

#include "money/coin_slot.h" 
#include "money/collected_coin.h"
#include "money/coin_storage.h"
#include "money/coin.h"
#include "money/coin_io.h"
#include "money/collected_coin_io.h"
#include "event/event_manager.h"
#include "money/change_drawer.h"
#include "money/change_dispenser.h"
#include "money/change_drawer_io.h"
#include "money/change_dispenser_io.h"
#include "money/coin_return.h"
#include "money/coin_return_io.h"
#include "money/money_handler.h"

void testing_valid_coin_creation(){
    Coin coin("QUARTER");
    assert(coin.getName() == "QUARTER");
    assert(coin.getNumericalValue() == 0.25);
}

void testing_invalid_coin_creation(){
    Coin coin("PENNY");
    assert(coin.getNumericalValue() == 0.0);
    assert(coin.isValidCoin("PENNY") == false);
}

void testing_add_and_remove_coin_coin_storage(){
    CoinStorage coinStorage;
    Coin coin("DIME");
    coinStorage.add_coin(coin);
    coinStorage.add_coin(coin);
    coinStorage.remove_coins("DIME", 1);
    assert(coinStorage.get_coin_count("DIME") == 1);
}

void testing_insert_valid_coin(){
    EventManager eventManager;
    CollectedCoin collectedCoin(&eventManager);
    CoinReturn coinReturn(&eventManager);
    CoinSlot coinSlot(&eventManager, &collectedCoin, 1.00, &coinReturn);
    coinSlot.startCoinInsertion(false);
}

void testing_coin_return(){
    EventManager eventManager;
    CollectedCoin collectedCoin(&eventManager);
    CoinReturn coinReturn(&eventManager);
    CoinSlot coinSlot(&eventManager, &collectedCoin, 1.00, &coinReturn);
    coinSlot.startCoinInsertion(false);
}

void testing_notify_funds_available(){
    EventManager eventManager;
    CollectedCoin collectedCoin(&eventManager);
    CoinReturn coinReturn(&eventManager);
    CoinSlot coinSlot(&eventManager, &collectedCoin, 1.00, &coinReturn);
    coinSlot.startCoinInsertion(false);
}

void testing_calculate_change_in_drawer(){
    /*
    ChangeDrawer::ChangeDrawer(EventManager* eventManager) : eventManager(eventManager), io(this) {
    // testing purposes
    coin_storage = {{"QUARTER", 12}, {"DIME", 20}, {"NICKEL", 15}};
}
    */
   EventManager eventManager;
   ChangeDrawer changeDrawer(&eventManager);
   changeDrawer.displayChangeLevels();
}

void testing_refill_change(){
    // ChangeDrawer::ChangeDrawer(EventManager* eventManager, std::unordered_map<std::string, int> max_capacity) : eventManager(eventManager), io(this), max_capacity_slot(max_capacity) {}
    EventManager eventManager;
    ChangeDrawer changeDrawer(&eventManager, {{"QUARTER", 20}, {"DIME", 20}, {"NICKEL", 20}});
    changeDrawer.onRefillChange();
}

void testing_change_dispenser(){
   EventManager eventManager; 
   ChangeDrawer changeDrawer(&eventManager);
   ChangeDispenser changeDispenser(&eventManager, &changeDrawer);

   EventData data;
   data.inserted_amount = 1.10;
   data.beverage_cost = 1.00;

   std::cout << "\nCHANGE BEFORE" << std::endl;
   changeDrawer.displayChangeLevels();

   changeDispenser.onGiveChange(data);

   std::cout << "\nCHANGE AFTER" << std::endl;
   changeDrawer.displayChangeLevels();
}


void testing_start_processing(){
    EventManager eventManager;
    CollectedCoin collectedCoin(&eventManager);
    CoinReturn coinReturn(&eventManager);
    CoinSlot coinSlot(&eventManager, &collectedCoin, 1.00, &coinReturn);
    ChangeDrawer changeDrawer(&eventManager);
    ChangeDispenser changeDispenser(&eventManager, &changeDrawer);
    MoneyHandler moneyHandler(&collectedCoin, &coinSlot, &changeDrawer, &changeDispenser, &eventManager, &coinReturn);
    moneyHandler.setState(MoneyHandlerState::Processing);
    /*
    CONSTRUCTOR:changeDispenser
      MoneyHandler(CollectedCoin* collectedCoin, 
      CoinSlot* coinSlot, 
      ChangeDrawer* changeDrawer, 
      ChangeDispenser* changeDispenser, 
      EventManager* eventManager, 
      CoinReturn* coinReturn);
    */

}

/*

int main(){
    std::cout << "Money Test Driver" << std::endl;
    testing_start_processing();

    
    
    return 0;
}
*/








 /*
    OLD TESTS
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

   // TESTING CHANGE DRAWER CHANGE INSERTION MAIINTENANCE
   std::unordered_map<std::string, int> max_capacity{
    {"NICKEL", 30},
    {"DIME", 30},
    {"QUARTER", 30}
};
ChangeDrawer changeDrawer2(&eventManager, max_capacity);
changeDrawer2.displayChangeLevels();
changeDrawer2.onRefillChange();
*/
