// collected_coin_io.h

#ifndef COLLECTED_COIN_IO_H
#define COLLECTED_COIN_IO_H

#include <iostream>
#include <unordered_map>

class CollectedCoin;
class CollectedCoinIO {
public:
    void displayCollectedMoney(double value, std::unordered_map<std::string, int> coins);
    CollectedCoinIO(CollectedCoin* owner);
private:
    CollectedCoin* collectedCoin;
};

#endif