#ifndef COIN_SLOT_IO_H
#define COIN_SLOT_IO_H

#include <iostream>

class CoinSlot;
class CoinSlotIO {
    public:
        CoinSlotIO(CoinSlot* owner);
        void insertCoins();
        void displayTotalinsertedCoins(double totalInsertedValue);
    private:
        CoinSlot* coin_slot;
};

#endif