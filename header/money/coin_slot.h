#ifndef COIN_SLOT_H
#define COIN_SLOT_H

#include "coin.h"
#include "event_manager.h"
#include <vector>
#include "coin_slot_io.h"

class CoinSlot{
    public:
        CoinSlot(EventManager* eventManager);
        void notifyFundsAvailable();
        void calculateInsertedValue();
    private:
        std::vector<Coin> totalInsertedMoney;
        double minimumValue;
        double totalInsertedValue;
        CoinSlotIO io;

        // EventManager* eventManager;
};

#endif