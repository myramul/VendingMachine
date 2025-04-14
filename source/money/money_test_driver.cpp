#include <iostream>
#include "money/coin_slot.h" 
#include "event/event_manager.h"

// g++ -Iheader source/money/coin_slot.cpp source/money/money_test_driver.cpp source/money/coin_slot_io.cpp source/money/coin.cpp -o vending_test

int main(){
    std::cout << "Money Test Driver" << std::endl;

    // TESTING COIN INSERTION
    EventManager eventManager;
    CoinSlot coinSlot(&eventManager, 1.00);
    coinSlot.startCoinInsertion();
    return 0;
}