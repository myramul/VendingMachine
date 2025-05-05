#include "dispenser/dispenser_container.h"
#include <iostream>

DispenserContainer::DispenserContainer(EventManager* manager)
    : bin(), state(DispenserState::Idle), eventManager(manager), io(this) {

    eventManager->registerListener(EventType::FundsAvailable, [this](const EventData& data) {
        this->onSufficientFunds(data);
    });

    eventManager->registerListener(EventType::MaintenanceMode, [this](const EventData&) {
        this->enterMaintenanceMode();
    });

    eventManager->registerListener(EventType::TransactionComplete, [this](const EventData&) {
        this->enterIdleMode();
    });
    // for demonstration
    storage = {
        Slot(1, 1.00, 3, {Beverage("Coke"), Beverage("Coke"), Beverage("Coke")}),
        Slot(2, 1.00, 3, {Beverage("Fanta"), Beverage("Fanta"), Beverage("Fanta")}),
        Slot(3, 1.00, 3, {Beverage("Water"), Beverage("Water"), Beverage("Water")}),
        Slot(4, 1.00, 3, {Beverage("Fanta"), Beverage("Fanta"), Beverage("Fanta")}),
        Slot(5, 1.00, 3, {Beverage("Coke"), Beverage("Coke"), Beverage("Coke")}),
        Slot(6, 1.00, 3, {Beverage("Sprite"), Beverage("Sprite"), Beverage("Sprite")}),
        Slot(7, 1.00, 3, {Beverage("Sprite"), Beverage("Sprite"), Beverage("Sprite")}),
        Slot(8, 1.00, 3, {Beverage("Water"), Beverage("Water"), Beverage("Water")})
    };
}

void DispenserContainer::selectBeverage() {
    io.displayMenu(storage);
    int selectedIndex = io.handleSelectionInput(storage);

    if (selectedIndex != -1) {
        Slot& selectedSlot = storage[selectedIndex];
        io.displaySelectedBeverage(selectedSlot.getFrontBeverage(), selectedSlot.getPrice());
        dispenseBeverage(selectedSlot.getFrontBeverage());
    } else {
        std::cout << "Invalid selection.\n";
    }
}

void DispenserContainer::dispenseBeverage(const Beverage& beverage) {

    selectedBeverage = beverage;

    for (Slot& slot : storage) {
        if (!slot.isEmpty() && slot.getFrontBeverage().getName() == beverage.getName()) {
            slot.popFrontBeverage();
            io.displayDispensedBeverage(beverage);
            
            if (bin.placeBeverage(beverage)) {
                EventData data;
                data.inserted_amount = insertedAmount;
                data.beverage_cost = slot.getPrice();
                data.slotID = slot.getID();
                data.beverage_name = beverage.getName();

                eventManager->notify(EventType::BeverageDispensed, data);
                return;

            }

            
        }
    }

    std::cout << "Error: Could not dispense beverage. Slot not found or empty.\n";
}

void DispenserContainer::onRefillBeverages() {
    setState(DispenserState::Maintenance);
    io.inputRefillBeverages(storage);
    setState(DispenserState::Idle);
}

void DispenserContainer::setState(DispenserState newState) {
    state = newState;
}

void DispenserContainer::onSufficientFunds(EventData data) {
    insertedAmount = data.inserted_amount;
    setState(DispenserState::Processing);
    selectBeverage();
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
            io.displaySelectedBeverage(selectedBeverage, slot.getPrice());
            break;
        }
    }
}

void DispenserContainer::collectItem() {
    bin.collectBeverage();   
}

void DispenserContainer::displayMenu() {
    io.displayMenu(storage);
}

std::string DispenserContainer::getState() const {
    switch (state) {
        case DispenserState::Idle: return "Idle";
        case DispenserState::Processing: return "Processing";
        case DispenserState::Maintenance: return "Maintenance";
        default: return "Unknown";
    }
}

std::vector<Slot>& DispenserContainer::getStorage() {
    return storage;
}

