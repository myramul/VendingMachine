// coin slot cpp

#include "money/coin_slot.h"

CoinSlot::CoinSlot(EventManager* eventManager, CollectedCoin* collectedCoin, double beverageCost) :
    eventManager(eventManager), collectedCoin(collectedCoin), minimumValue(beverageCost), totalInsertedValue(0), io(this) {

        // Register event listeners for transaction completion
        eventManager->registerListener(EventType::TransactionComplete,
            [this](const EventData& data) {
                this->onResetForNewTransaction();
            }
        );
}

void CoinSlot::notifyFundsAvailable() {
    std::cout << "FUNDS AVAILABLE" << std::endl;
    
    EventData data;
    data.inserted_amount = totalInsertedValue;
    data.beverage_cost = minimumValue;
    eventManager->notify(EventType::FundsAvailable, data);
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

void CoinSlot::startCoinInsertion(bool exactChangeMode) {
    io.insertCoins(exactChangeMode);
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
    std::cout << "Coin slot reset for new transaction." << std::endl;
}