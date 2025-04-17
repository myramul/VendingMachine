// coin storage h

#ifndef COIN_STORAGE_H
#define COIN_STORAGE_H

#include <unordered_map>
#include <string>
#include "money/coin.h"

class CoinStorage {
public:
    CoinStorage();
    virtual void add_coin(Coin coin);
    virtual void remove_coins(std::string name, int quantity);
    virtual int get_coin_count(std::string name);
protected:
    std::unordered_map<std::string, int> coin_storage;
    double calculate_total_value();
    double total_value;
};

#endif
