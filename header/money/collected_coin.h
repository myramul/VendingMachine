// collected_coin.h

#ifndef COLLECTED_COIN_H
#define COLLECTED_COIN_H

#include "money/coin_storage.h"
#include "money/collected_coin_io.h"
#include "event/event_manager.h"

class CollectedCoin : public CoinStorage {
    public:
      CollectedCoin(EventManager* eventManager);
      CollectedCoin(std::unordered_map<std::string, int> coin_storage, EventManager* eventManager);
      void onCollectMoney();
    private:
      CollectedCoinIO io;
      EventManager* eventManager;

      friend class CollectedCoinIO;
};

#endif