#include "dispenser/dispenser_container.h"
#include <iostream>

DispenserContainer::DispenserContainer(EventManager* manager, DispenserContainerIO* ioPtr)
    : bin("MainBin"), state(DispenserState::Idle), eventManager(manager), io(ioPtr) {

    // Triggered when funds are sufficient (after coin insertion)
    eventManager->registerListener(EventType::FundsAvailable,
        [this](const EventData& data) {
            this->onSufficientFunds(data);
        }
    );

    // Maintenance staff triggers a refill (optional, depends on UI input)
    eventManager->registerListener(EventType::RefillRequested,
        [this](const EventData&) {
            this->onRefillBeverages();
        }
    );

    // Maintenance staff enters maintenance mode
    eventManager->registerListener(EventType::EnterMaintenance,
        [this](const EventData&) {
            this->enterMaintenanceMode();
        }
    );

    // Optional: Reset state to Idle after a transaction completes
    eventManager->registerListener(EventType::TransactionComplete,
        [this](const EventData&) {
            this->enterIdleMode();
        }
    );
}

void DispenserContainer::selectBeverage() {
    io->displayMenu();
    io->handleSelectionInput();
}

void DispenserContainer::dispenseBeverage(const Beverage& beverage) {
    std::cout << "Dispensing " << beverage.getName() << "...\n";

    // Save selected beverage
    selectedBeverage = beverage;

    // Remove beverage from slot
    for (Slot& slot : storage) {
        if (!slot.isEmpty() && slot.getFrontBeverage().getName() == beverage.getName()) {
            slot.popFrontBeverage();
            // Notify UI
            io->displayDispensedBeverage();

            // Notify event manager with actual pricing info
            EventData data;
            data.inserted_amount = insertedAmount; // you must store this when funds are inserted
            data.beverage_cost = slot.getPrice();
            eventManager->notify(EventType::BeverageDispensed, data);

            return;
        }
    }

    // If no slot matched (error fallback)
    std::cout << "Error: Could not dispense beverage. Slot not found or empty.\n";
}

void DispenserContainer::onRefillBeverages() {
    setState(DispenserState::Maintenance);
    io->inputRefillBeverages();
    setState(DispenserState::Idle);
}

void DispenserContainer::setState(DispenserState newState) {
    state = newState;
}


    void DispenserContainer::onSufficientFunds(EventData data) {
        // 1. Store the amount inserted by the user
        insertedAmount = data.inserted_amount;

        // 2. Set the machine to processing mode
        setState(DispenserState::Processing);

        // 3. Start beverage selection flow
        selectBeverage();  // This will call io->displayMenu(), then handle input, then call dispenseBeverage()

        // When beverage is dispensed, dispenseBeverage() will call notifyGiveChange() using insertedAmount
    }



void DispenserContainer::notifyGiveChange() {
    EventData data;

    data.inserted_amount = insertedAmount;

    // Find beverage cost from the slot that contains selectedBeverage
    for (const Slot& slot : storage) {
        if (!slot.isEmpty() && slot.getFrontBeverage().getName() == selectedBeverage.getName()) {
            data.beverage_cost = slot.getPrice();
            break;
        }
    }

    eventManager->notify(EventType::BeverageDispensed, data);
}

bool DispenserContainer::enterMaintenanceMode() {
    setState(DispenserState::Maintenance);  
    return true;
}

bool DispenserContainer::enterProcessingMode() {
    setState(DispenserState::Processing);
    return true;
}

bool DispenserContainer::enterIdleMode() {
    setState(DispenserState::Idle);
    return true;
}

void DispenserContainer::setDispensedBeverage() {
    io->displaySelectedBeverage();
}

void DispenserContainer::collectItem() {
    std::cout << "Item collected.\n";
}

std::string DispenserContainer::getState() const {
    switch (state) {
    case DispenserState::Idle:
        return "Idle";
    case DispenserState::Processing:
        return "Processing";
    case DispenserState::Maintenance:
        return "Maintenance";
    default:
        return "Unknown";
    }
}


