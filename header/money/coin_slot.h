#ifndef COIN_SLOT_H
#define COIN_SLOT_H

#include "money/coin.h"
#include "event/event_manager.h"
#include <vector>
#include "money/coin_slot_io.h"
#include "money/collected_coin.h"

class CoinSlot{
    public:
        CoinSlot(EventManager* eventManager, CollectedCoin* collectedCoin, double beverageCost);
        void notifyFundsAvailable();
        void calculateInsertedValue();
        void startCoinInsertion();
        void addCoin(const Coin& coin);
        double getTotalInsertedValue() const; 
        double getMinimumValue() const;
        void onResetForNewTransaction();     
    
    private:
        std::vector<Coin> totalInsertedMoney;
        double minimumValue;
        double totalInsertedValue;
        CoinSlotIO io;
        EventManager* eventManager;
        CollectedCoin* collectedCoin;

        friend class CoinSlotIO;
        void addMoneyToCollection();
};

#endif