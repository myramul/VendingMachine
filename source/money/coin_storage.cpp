// coin storage cpp
#include "money/coin_storage.h"

CoinStorage::CoinStorage() {
    coin_storage = {{"QUARTER", 0}, {"DIME", 0}, {"NICKEL", 0}};
    total_value = 0.0;
}

void CoinStorage::add_coin(Coin coin) {
    coin_storage[coin.getName()]++;
}

void CoinStorage::remove_coins(std::string name, int quantity) {
    if (coin_storage[name] >= quantity) {
        coin_storage[name] -= quantity;
    }
}

int CoinStorage::get_coin_count(std::string name) {
    return coin_storage[name];
}

double CoinStorage::calculate_total_value() {
    total_value = coin_storage["QUARTER"] * 0.25 +
                  coin_storage["DIME"] * 0.10 +
                  coin_storage["NICKEL"] * 0.05;
    return total_value;
}
