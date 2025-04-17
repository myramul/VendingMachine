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
    // add in logic to register event listeners here look at coin slot and change dispenser as examples
    // this should listen to transaction complete and the callback should be onTransactionComplete

}


void VendingMachine::setState(const std::string& newState) {
    state = newState;
}

void VendingMachine::enterMaintenanceMode() {
    setState("Maintenance");
    std::cout << "Machine is now in maintenance mode.\n";
    // SHOULD SEND A FLAG TO THE EVENT MANAGER TO INDICATE THAT THE MACHINE IS IN MAINTENANCE
    // using the evnt manager notify function, look at the event manager h file for details
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
    // should call the moeny to start accepting coins and send a flag to the event manager processing
}

void VendingMachine::initializeMachine() {
    // THIS SHOULD BE THE FUNCTION THAT INTIALIZES THE MACHIEN THE FIRST TIME
    // SO IT SHOW THE MAINTENANCE MENU
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
