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

    // Maintenance triggers refill
    eventManager->registerListener(EventType::MaintenanceMode,
        [this](const EventData&) {
            this->onRefillBeverages();
        }
    );

    // Reset to Idle after transaction complete
    eventManager->registerListener(EventType::TransactionComplete,
        [this](const EventData&) {
            this->enterIdleMode();
        }
    );
}

void DispenserContainer::selectBeverage() {
    io->displayMenu(storage);   // Display beverages dynamically
    int selectedIndex = io->handleSelectionInput(storage);  // Get user choice

    if (selectedIndex != -1) {
        Slot& selectedSlot = storage[selectedIndex];
        io->displaySelectedBeverage(selectedSlot.getFrontBeverage(), selectedSlot.getPrice());
        dispenseBeverage(selectedSlot.getFrontBeverage());
    } else {
        std::cout << "Invalid selection.\n";
    }
}

void DispenserContainer::dispenseBeverage(const Beverage& beverage) {
    std::cout << "Dispensing " << beverage.getName() << "...\n";
    selectedBeverage = beverage;

    for (Slot& slot : storage) {
        if (!slot.isEmpty() && slot.getFrontBeverage().getName() == beverage.getName()) {
            slot.popFrontBeverage();   // Remove beverage from slot
            io->displayDispensedBeverage(beverage);  // Notify user

            // Notify event manager with payment details
            EventData data;
            data.inserted_amount = insertedAmount;
            data.beverage_cost = slot.getPrice();
            data.slotID = slot.getID();

            eventManager->notify(EventType::BeverageDispensed, data);
            return;
        }
    }

    std::cout << "Error: Could not dispense beverage. Slot not found or empty.\n";
}

void DispenserContainer::onRefillBeverages() {
    setState(DispenserState::Maintenance);
    io->inputRefillBeverages(storage);   // Maintenance refill logic
    setState(DispenserState::Idle);
}

void DispenserContainer::setState(DispenserState newState) {
    state = newState;
}

void DispenserContainer::onSufficientFunds(EventData data) {
    insertedAmount = data.inserted_amount;
    setState(DispenserState::Processing);
    selectBeverage();  // Start selection after funds confirmed
}

void DispenserContainer::notifyGiveChange() {
    EventData data;
    data.inserted_amount = insertedAmount;

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
    for (const Slot& slot : storage) {
        if (!slot.isEmpty() && slot.getFrontBeverage().getName() == selectedBeverage.getName()) {
            io->displaySelectedBeverage(selectedBeverage, slot.getPrice());
            break;
        }
    }
}

void DispenserContainer::collectItem() {
    std::cout << "Item collected.\n";
    eventManager->notify(EventType::TransactionComplete, {});
}

std::string DispenserContainer::getState() const {
    switch (state) {
        case DispenserState::Idle: return "Idle";
        case DispenserState::Processing: return "Processing";
        case DispenserState::Maintenance: return "Maintenance";
        default: return "Unknown";
    }
}


