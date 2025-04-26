#ifndef COIN_RETURN_H
#define COIN_RETURN_H

#include "money/coin.h"
#include "money/coin_return_io.h"
#include "event/event_manager.h"
#include <vector>

class CoinReturn{
    public:
        CoinReturn(EventManager* eventManager);
        void returnCoins(std::vector<Coin> totalInsertedMoney);
    private:
        CoinReturnIO io;
        EventManager* eventManager;
};

#endif