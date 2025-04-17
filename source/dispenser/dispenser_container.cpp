#include "dispenser/dispenser_container.h"
#include <iostream>

DispenserContainer::DispenserContainer(EventManager* manager, DispenserContainerIO* ioPtr)
    : bin("MainBin"), state("Idle"), eventManager(manager), io(ioPtr) {}

void DispenserContainer::selectBeverage() {
    io->displayMenu();
    io->handleSelectionInput();
}

void DispenserContainer::dispenseBeverage(const Beverage& beverage) {
    std::cout << "Dispensing " << beverage.getName() << "...\n";
    selectedBeverage = beverage;
    io->displayDispensedBeverage();
}

void DispenserContainer::onRefillBeverages() {
    setState("Filling");
    io->inputRefillBeverages();
    setState("Idle");
}

void DispenserContainer::setState(const std::string& newState) {
    state = newState;
}

void DispenserContainer::onSufficientFunds() {
    std::cout << "Payment accepted.\n";
}

void DispenserContainer::notifyGiveChange() {
    std::cout << "Please take your change.\n";
}

bool DispenserContainer::enterMaintenanceMode() {
    setState("Maintenance");
    return true;
}

bool DispenserContainer::enterProcessingMode() {
    setState("Processing");
    return true;
}

bool DispenserContainer::enterIdleMode() {
    setState("Idle");
    return true;
}

void DispenserContainer::setDispensedBeverage() {
    io->displaySelectedBeverage();
}

void DispenserContainer::collectItem() {
    std::cout << "Item collected.\n";
}

std::string DispenserContainer::getState() const {
    return state;
}
