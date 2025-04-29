// money handler cpp

#include "money/money_handler.h"

MoneyHandler::MoneyHandler(CollectedCoin* collectedCoin, CoinSlot* coinSlot, ChangeDrawer* changeDrawer, ChangeDispenser* changeDispenser, EventManager* eventManager, CoinReturn* coinReturn) 
: coinSlot(coinSlot), 
changeDrawer(changeDrawer), 
changeDispenser(changeDispenser), 
eventManager(eventManager), 
coinReturn(coinReturn),
collectedCoin(collectedCoin){
     // Register event listeners for transaction completion
     eventManager->registerListener(EventType::TransactionComplete,
        [this](const EventData& data) {
            this->onResetForNewTransaction();
        }
    );

    eventManager->registerListener(EventType::StartCoinAccepting, 
        [this](const EventData& data) {
            this->setState(MoneyHandlerState::Processing);
    });

    eventManager->registerListener(EventType::MaintenanceMode, 
    [this](const EventData& data){
        this->setState(MoneyHandlerState::Maintenance);
    });
}

void MoneyHandler::setState(MoneyHandlerState newState) {
    switch (newState) {
        case MoneyHandlerState::Idle:
            enterIdleState();
            break;
        case MoneyHandlerState::Processing:
            enterProcessingState();
            break;
        case MoneyHandlerState::Maintenance:
            enterMaintenanceMode();
            break;
    }
}

void MoneyHandler::enterIdleState() {
    // std::cout << "[MoneyHandler] Entering Idle State.\n";
    state = MoneyHandlerState::Idle;
}

void MoneyHandler::enterProcessingState() {
   std::cout << "[MoneyHandler] Entering Processing State.\n";

    exactChangeMode = isExactChangeRequired();
    state = MoneyHandlerState::Processing;
    coinSlot->startCoinInsertion(exactChangeMode);
}

void MoneyHandler::enterMaintenanceMode() {
    // std::cout << "[MoneyHandler] Entering Maintenance Mode.\n";
    state = MoneyHandlerState::Maintenance;
}

bool MoneyHandler::isExactChangeRequired() const {
    return changeDrawer->getTotalChange() <= 0.20;
}

void MoneyHandler::onResetForNewTransaction() {
    // std::cout << "[MoneyHandler] Resetting for new transaction.\n";
    setState(MoneyHandlerState::Idle);
}

void MoneyHandler::refillChange() {
    if (state == MoneyHandlerState::Maintenance) {
        changeDrawer->onRefillChange();
    }
}

void MoneyHandler::collectMoney() {
    if (state == MoneyHandlerState::Maintenance) {
        collectedCoin->onCollectMoney();
    }
}