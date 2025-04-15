// Collectd coin cpp

#include "money/collected_coin_io.h"
#include "money/collected_coin.h"

void CollectedCoinIO::displayCollectedMoney(double value, std::unordered_map<std::string, int> coins) {
    std::cout << "Money collected total: $" << value << std::endl;
    for (auto& coin : coins) {
        std::cout << coin.first << ": x" << coin.second << std::endl;
    }
}

CollectedCoinIO::CollectedCoinIO(CollectedCoin* owner) : collectedCoin(owner) {
}