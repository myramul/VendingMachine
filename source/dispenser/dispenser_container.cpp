#include "dispenser/dispenser_container.h"
#include <iostream>

DispenserContainer::DispenserContainer(EventManager* manager, DispenserContainerIO* ioPtr)
    : bin("MainBin"), state("Idle"), eventManager(manager), io(ioPtr) {
        // ADD EVENT MANAGER REGISTER LISTENERS LOGIC HERE
        // LOOK AT THE COIN SLOT AND CHANGE DISPENSER AS AN EXAMPLE
        // AND ALSO LOOK AT THE LOGIC OF THE EVENT MANAGER
    }

void DispenserContainer::selectBeverage() {
    io->displayMenu();
    io->handleSelectionInput();
}

void DispenserContainer::dispenseBeverage(const Beverage& beverage) {
    std::cout << "Dispensing " << beverage.getName() << "...\n";
    selectedBeverage = beverage;
    io->displayDispensedBeverage();
    notifyGiveChange(); // MAKING CALL TO EVENT MANAGER THAT BEV HAS BEEN DISPENSED
}

void DispenserContainer::onRefillBeverages() {
    setState("Filling"); // NOT a string
    io->inputRefillBeverages();
    setState("Idle"); // not a string
}

void DispenserContainer::setState(DispenserState newState) {
    state = newState;
}

void DispenserContainer::onSufficientFunds(EventData data) {
    // ADD IN LOGIC HERE TO BEGIN BEVERAGE SELECTION and PROCESSING
    // YOU MIGHT HAVE TO STORE THE INSERTED AMOUNT (data.inserted_amount) IN A VARIABLE 
    // AND THEN PASS IT BACK TO THE EVENT MANAGER WHEN GIVING CHANGE
}


void DispenserContainer::notifyGiveChange() {
    // MAKE CALL TO EVENT MANAGER, WITH THE MONEY PUT IN AND THE BEVERAGE COST
    EventData data;
   // data.inserted_amount = ; ADD IN THE CORRECT VALUES
   // data.beverage_cost = ; ADD IN THE CORRECT VALUES
    eventManager->notify(EventType::BeverageDispensed, data);
}

bool DispenserContainer::enterMaintenanceMode() {
    setState("Maintenance"); // NOT A STRING
    return true;
}

bool DispenserContainer::enterProcessingMode() {
    setState("Processing"); // NOT A STRING
    return true;
}

bool DispenserContainer::enterIdleMode() {
    setState("Idle"); // NOT A STRING
    return true;
}

void DispenserContainer::setDispensedBeverage() {
    io->displaySelectedBeverage();
}

void DispenserContainer::collectItem() {
    std::cout << "Item collected.\n";
}

std::string DispenserContainer::getState() const {
    return state; // NOT A STRING
}
