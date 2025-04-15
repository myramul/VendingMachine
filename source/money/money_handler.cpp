// money handler cpp

#include "money/money_handler.h"

MoneyHandler::MoneyHandler(CollectedCoin* collectedCoin, CoinSlot* coinSlot, ChangeDrawer* changeDrawer, ChangeDispenser* changeDispenser, EventManager* eventManager) 
: coinSlot(coinSlot), 
changeDrawer(changeDrawer), 
changeDispenser(changeDispenser), 
eventManager(eventManager), 
collectedCoin(collectedCoin){
    /*
     // Register event listeners for transaction completion
     eventManager->registerListener(EventType::TransactionComplete,
        [this](const EventData& data) {
            this->resetForNewTransaction();
        }
    );
    */
}

void MoneyHandler::setState(MoneyHandlerState newState) {
    switch (newState) {
        case MoneyHandlerState::Idle:
            if (enterIdleState()) {
                state = MoneyHandlerState::Idle;
            }
            break;
        case MoneyHandlerState::Processing:
            if (enterProcessingState()) {
                state = MoneyHandlerState::Processing;
            }
            break;
        case MoneyHandlerState::Maintenance:
            if (enterMaintenanceMode()) {
                state = MoneyHandlerState::Maintenance;
            }
            break;
    }
}

bool MoneyHandler::enterIdleState() {
    std::cout << "[MoneyHandler] Entering Idle State.\n";
    exactChangeMode = isExactChangeRequired();
    return true;
}

bool MoneyHandler::enterProcessingState() {
    std::cout << "[MoneyHandler] Entering Processing State.\n";

    if (isExactChangeRequired()) {
        std::cout << "Exact change required. Not enough change in the drawer.\n";
        exactChangeMode = true;
    } else {
        exactChangeMode = false;
    }

    // Start coin insertion
    coinSlot->startCoinInsertion();
    return true;
}

bool MoneyHandler::enterMaintenanceMode() {
    std::cout << "[MoneyHandler] Entering Maintenance Mode.\n";
    return true;
}

bool MoneyHandler::isExactChangeRequired() const {
    return changeDrawer->getTotalChange() <= 0.25;
}

void MoneyHandler::onResetForNewTransaction() {
    std::cout << "[MoneyHandler] Resetting for new transaction.\n";
    setState(MoneyHandlerState::Idle);
}