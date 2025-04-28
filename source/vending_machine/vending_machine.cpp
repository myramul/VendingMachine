#include "vending_machine/vending_machine.h"
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
{
    // Register event listener for transaction complete
    eventManager->registerListener(EventType::TransactionComplete,
        [this](const EventData& data) {
            this->onTransactionComplete();
        }
    );
}

void VendingMachine::setState(const std::string& newState) {
    state = newState;
}

void VendingMachine::enterMaintenanceMode() {
    setState("Maintenance");
    std::cout << "Machine is now in maintenance mode.\n";

    // Notify event manager that machine entered maintenance mode
    EventData data;
    data.message = "Entering Maintenance Mode";
    eventManager->notify(EventType::MaintenanceMode, data);
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

    // Notify event manager that machine entered idle mode
    EventData data;
    data.message = "Entering Idle Mode";
    eventManager->notify(EventType::IdleMode, data);
}

void VendingMachine::enterProcessingMode() {
    setState("Processing");
    std::cout << "Entering processing mode.\n";

    // Notify event manager to start accepting coins
    EventData data;
    data.message = "Start Coin Accepting";
    eventManager->notify(EventType::StartCoinAccepting, data);
}

void VendingMachine::initializeMachine() {
    // Initialize machine: show maintenance menu (idle for now)
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
