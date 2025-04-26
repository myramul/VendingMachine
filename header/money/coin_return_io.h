#include <vector>
#include "money/coin.h"

class CoinReturn;

class CoinReturnIO {
    public:
        void displayReturnCoins(std::vector<Coin> totalInsertedMoney);
};