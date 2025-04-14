#include "money/coin_slot.h"

CoinSlot::CoinSlot(EventManager* eventManager, double min) :
    eventManager(eventManager), minimumValue(min), totalInsertedValue(0), io(this) {}

void CoinSlot::notifyFundsAvailable() {
    std::cout << "FUNDS AVAILABLE" << std::endl;
    /*
    EventData data;
    data.amount = totalInsertedValue;
    eventManager->notify(EventType::FundsAvailable, data);
    */
}

void CoinSlot::calculateInsertedValue() {
    totalInsertedValue = 0;
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

void CoinSlot::startCoinInsertion() {
    io.insertCoins();
}