#ifndef COLLECTED_COIN_H
#define COLLECTED_COIN_H

#include "coin_storage.h"
#include "collected_coin_io.h"

class CollectedCoin : public CoinStorage {
    public:
      CollectedCoin();
      void onCollectMoney();
    private:
      CollectedCoinIO io;
};

#endif