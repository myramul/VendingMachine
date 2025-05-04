// change_dispenser.cpp
#include "money/change_dispenser.h"
#include <cmath>


ChangeDispenser::ChangeDispenser(EventManager* eventManager, ChangeDrawer* changeDrawer) :
    eventManager(eventManager), total_change(0.0), changeDrawer(changeDrawer), io(this) {
        
        // Register event listeners for transaction completion
        eventManager->registerListener(EventType::TransactionComplete,
            [this](const EventData& data) {
                this->onResetForNewTransaction();
            }
        );

        // register event for BeverageDispened
        eventManager->registerListener(EventType::BeverageDispensed,
            [this](const EventData& data) {
                this->onGiveChange(data);
            }
        );
    }

void ChangeDispenser::onGiveChange(EventData data) {
    if (changeDrawer->getTotalChange() <= 0.20) {
        io.displayReturnedChange(0.0);
        eventManager->notify(EventType::TransactionComplete, data);
        return;
    }else{
        double inserted = data.inserted_amount;
        double cost = data.beverage_cost;
        double changeAmount = inserted - cost;

        if (changeAmount < 0.005) {
            io.displayReturnedChange(0.0);
            eventManager->notify(EventType::TransactionComplete, data);
            return;
        }

        calculateChange(changeAmount);
        io.displayReturnedChange(changeAmount);
        eventManager->notify(EventType::TransactionComplete, data);
    }
}

void ChangeDispenser::calculateChange(double changeAmount) {
    std::unordered_map<std::string, double> coin_values = Coin::coin_values;

    for (const auto& [name, value] : coin_values) {
        int count = 0;
        while (changeAmount >= value - 0.001 && changeDrawer->get_coin_count(name) > 0) {
            changeDrawer->remove_coins(name, 1);
            changeAmount -= value;
            changeAmount = std::round(changeAmount * 100.0) / 100.0;
            count++;
        }
        if (count > 0) {
            std::cout << "\n\n" << name << ": x" << count << std::endl;
        }
    }
}

void ChangeDispenser::onResetForNewTransaction() {
    total_change = 0.0;
    // std::cout << "Change dispenser reset for new transaction." << std::endl; 
}