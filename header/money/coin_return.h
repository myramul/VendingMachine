#include "money/coin.h"
#include "money/coin_return_io.h"
#include <vector>

class CoinReturn{
    public:
        void returnCoins(std::vector<Coin> totalInsertedMoney);
    private:
        CoinReturnIO io;
};