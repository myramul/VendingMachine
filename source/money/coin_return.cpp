#include "money/coin_return.h"
#include <vector>
#include <string>
#include "money/coin_io.h"


void CoinReturn::returnCoins(std::vector<Coin> totalInsertedMoney) {
    io.returnCoins(totalInsertedMoney);
    eventManager.notify(EventType::TransactionComplete, EventData{});
}