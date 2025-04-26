#include "money/coin_return.h"
#include <vector>
#include <string>
#include "money/coin_io.h"

CoinReturn::CoinReturn(EventManager* eventManager) : eventManager(eventManager) {}

void CoinReturn::returnCoins(std::vector<Coin> totalInsertedMoney) {
    io.displayReturnCoins(totalInsertedMoney);
    eventManager->notify(EventType::TransactionComplete, EventData{});
}