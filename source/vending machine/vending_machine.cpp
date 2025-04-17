#include "vending machine/vending_machine.h"
#include <iostream>

VendingMachine::VendingMachine(
    const std::string& password,
    EventManager* em,
    MoneyHandler* mh,
    DispenserContainer* dc,
    ReportManager* rm)
    : maintenancePassword(password),
      state("Idle"),
      eventManager(em),
      moneyComponent(mh),
      dispenserComponent(dc),
      reportManager(rm)
{}

void VendingMachine::setState(const std::string& newState) {
    state = newState;
}

void VendingMachine::enterMaintenanceMode() {
    setState("Maintenance");
    std::cout << "Machine is now in maintenance mode.\n";
}

bool VendingMachine::unlockMachine(const std::string& inputPassword) {
    return inputPassword == maintenancePassword;
}

void VendingMachine::lockMachine() {
    setState("Idle");
    std::cout << "Machine is now locked.\n";
}

void VendingMachine::enterIdleMode() {
    setState("Idle");
    std::cout << "Entering idle mode.\n";
}

void VendingMachine::enterProcessingMode() {
    setState("Processing");
    std::cout << "Entering processing mode.\n";
}

void VendingMachine::initializeMachine() {
    enterIdleMode();
    std::cout << "Vending machine initialized.\n";
}

bool VendingMachine::authenticateMaintenancePasscode(const std::string& inputPasscode) {
    return unlockMachine(inputPasscode);
}

void VendingMachine::onTransactionComplete() {
    std::cout << "Transaction completed. Returning to idle mode.\n";
    enterIdleMode();
}
