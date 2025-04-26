#ifndef COIN_RETURN_IO_H
#define COIN_RETURN_IO_H

#include <vector>
#include "money/coin.h"

class CoinReturn;

class CoinReturnIO {
    public:
        void displayReturnCoins(std::vector<Coin> totalInsertedMoney);
};

#endif