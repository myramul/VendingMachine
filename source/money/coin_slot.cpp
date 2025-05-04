// coin slot cpp

#include "money/coin_slot.h"

CoinSlot::CoinSlot(EventManager* eventManager, CollectedCoin* collectedCoin, double beverageCost, CoinReturn* coinReturn) :
    eventManager(eventManager), collectedCoin(collectedCoin), minimumValue(beverageCost), totalInsertedValue(0), io(this), coinReturn(coinReturn) {

        eventManager->registerListener(EventType::TransactionComplete,
            [this](const EventData& data) {
                this->onResetForNewTransaction();
            }
        );
}

void CoinSlot::notifyFundsAvailable() {
    
    EventData data;
    data.inserted_amount = totalInsertedValue;
    data.beverage_cost = minimumValue;
    eventManager->notify(EventType::FundsAvailable, data);
}

void CoinSlot::calculateInsertedValue() {
    totalInsertedValue = 0.00;
    for (Coin& c : totalInsertedMoney) {
        totalInsertedValue += c.getNumericalValue();
    }
}

void CoinSlot::addCoin(const Coin& coin) {
    totalInsertedMoney.push_back(coin);
    calculateInsertedValue();
}

double CoinSlot::getTotalInsertedValue() const {
    return totalInsertedValue;
}

double CoinSlot::getMinimumValue() const {
    return minimumValue;
}

void CoinSlot::startCoinInsertion(bool exactChangeMode) {
    io.insertCoins(exactChangeMode, coinReturn);
}

void CoinSlot::addMoneyToCollection(){
    for (Coin& c : totalInsertedMoney) {
        collectedCoin->add_coin(c);
    }
}

void CoinSlot::onResetForNewTransaction(){
    addMoneyToCollection();
    totalInsertedMoney.clear();
    totalInsertedValue = 0;
}