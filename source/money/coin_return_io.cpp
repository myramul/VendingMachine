#include "money/coin_return_io.h"

void CoinReturnIO::displayReturnCoins(std::vector<Coin> totalInsertedMoney) {
    std::cout << "Returning coins: ";
    for (Coin coin : totalInsertedMoney) {
        std::cout << coin.getName() << "\n";
    }
    std::cout << std::endl;
    std::cout << "Coins returned.\n Transaction Complete." << std::endl;
}


