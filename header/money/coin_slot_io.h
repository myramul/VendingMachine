// coin_slot_io.h

#ifndef COIN_SLOT_IO_H
#define COIN_SLOT_IO_H

#include <iostream>
#include <iomanip>
#include "money/coin_return.h"

class CoinSlot;
class CoinSlotIO {
    public:
        CoinSlotIO(CoinSlot* owner);
        void insertCoins(bool exactChangeMode, CoinReturn* coinReturn);
        void displayTotalinsertedCoins(double totalInsertedValue);
    private:
        CoinSlot* coin_slot;
};

#endif