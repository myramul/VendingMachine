#include <iostream>
#include "money/coin_slot.h" 
#include "event/event_manager.h"

// g++ -Iheader source/money/coin_slot.cpp source/money/money_test_driver.cpp source/money/coin_slot_io.cpp source/money/coin.cpp -o vending_test

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
   collectedCoin.onCollectMoney();
    return 0;
}