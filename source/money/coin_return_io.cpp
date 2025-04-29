#include "money/coin_return_io.h"

void CoinReturnIO::displayReturnCoins(std::vector<Coin> totalInsertedMoney) {
    std::cout << "\nRETURNING COINS: \n";
    for (Coin coin : totalInsertedMoney) {
        std::cout << coin.getName() << "\n";
    }
    std::cout << std::endl;
    std::cout << "Coins returned.\nTransaction Complete." << std::endl;
}


