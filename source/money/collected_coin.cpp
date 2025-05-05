// collected coin cpp

#include "money/collected_coin.h"
#include "money/collected_coin_io.h"
#include <iostream>

CollectedCoin::CollectedCoin(EventManager* eventManager) 
    : eventManager(eventManager), io(this) {
}

// constructor for testing
CollectedCoin::CollectedCoin(std::unordered_map<std::string, int> coin_storage, EventManager* eventManager)
    : eventManager(eventManager), io(this) {
    this->coin_storage = coin_storage;
    calculate_total_value();
}

void CollectedCoin::onCollectMoney() {
    io.displayCollectedMoney(total_value, coin_storage);
    total_value = 0.0;
    coin_storage["QUARTER"] = 0;
    coin_storage["DIME"] = 0;
    coin_storage["NICKEL"] = 0;
}
