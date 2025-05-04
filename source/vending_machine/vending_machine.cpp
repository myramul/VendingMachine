// vending_machine.cpp
// nodira kazakova

#include "vending_machine/vending_machine.h"
#include "vending_machine/vending_machine_io.h"
#include <iostream>

VendingMachine::VendingMachine::VendingMachine(
    const std::string& password,
    EventManager* em,
    MoneyHandler* mh,
    DispenserContainer* dc,
    ReportManager* rm)
    : maintenancePassword(password),
    state(VendingMachineState::Idle),
    eventManager(em),
    moneyComponent(mh),
    dispenserComponent(dc),
    reportManager(rm),
    io(this)
{
    eventManager->registerListener(EventType::TransactionComplete,
        [this](const EventData& data) {
            this->onTransactionComplete(data);
        }
    );
}

void VendingMachine::setState(VendingMachineState newState) {
    state = newState;
}


void VendingMachine::enterMaintenanceMode() {
    setState(VendingMachineState::Maintenance);
    std::cout << "Machine is now in maintenance mode.\n";

    /*
    // Log maintenance opening
    if (reportManager && moneyComponent && dispenserComponent) {
        auto changeLevels = moneyComponent->getChangeLevels();
        double moneyCollected = moneyComponent->getTotalMoney();
        auto slotContents = dispenserComponent->getSlotContents();

        reportManager->logMaintenanceOpening(changeLevels, moneyCollected, slotContents);
    }
    */

    EventData data;
    data.message = "Entering Maintenance Mode";
    eventManager->notify(EventType::MaintenanceMode, data);
}


bool VendingMachine::unlockMachine(const std::string& inputPassword) {
    return inputPassword == maintenancePassword;
}

void VendingMachine::lockMachine() {
    std::cout << "Machine is now locked.\n";
    startMachine();
}


void VendingMachine::enterIdleMode() {
    setState(VendingMachineState::Idle);

    EventData data;
    data.message = "Entering Idle Mode";
    eventManager->notify(EventType::IdleMode, data);
}

void VendingMachine::enterProcessingMode() {
    setState(VendingMachineState::Processing);
    std::cout << "Entering processing mode.\n";

    EventData data;
    data.message = "Start Coin Accepting";
    eventManager->notify(EventType::StartCoinAccepting, data);
}

void VendingMachine::initializeMachine() {
    enterIdleMode();
    std::cout << "Vending machine initialized.\n";
}

bool VendingMachine::authenticateMaintenancePasscode(const std::string& inputPasscode) {
    return unlockMachine(inputPasscode);
}

void VendingMachine::onTransactionComplete(const EventData& data) {
    // Log transaction
    if (reportManager) {
        reportManager->logTransaction(data.beverage_name, data.inserted_amount, (data.inserted_amount - data.beverage_cost));
    }

    enterIdleMode();
    startMachine();
}

void VendingMachine::collectMoney() {
    moneyComponent->collectMoney();
    std::cout << "Money collected successfully.\n";
}

void VendingMachine::refillChange() {
    moneyComponent->refillChange();
}

void VendingMachine::refillBeverages() {
   dispenserComponent->onRefillBeverages(); 
}

void VendingMachine::viewReports() {
    std::cout << "[TODO] displayReports() not implemented in ReportManager yet.\n";
    // reportManager->displayReports();
}

void VendingMachine::displayMenu() {
    dispenserComponent->displayMenu();
}

void VendingMachine::startMachine(){
    io.displayWelcomeMessage();
}

/*
// New maintenance functions
void VendingMachine::collectMoney() {
    moneyComponent->collectMoney();
    std::cout << "Money collected successfully.\n";
}

void VendingMachine::refillChange() {
    moneyComponent->refillChange();
    std::cout << "Change refilled successfully.\n";
}

void VendingMachine::refillBeverages() {
    dispenserComponent->refillAll();
    std::cout << "Beverages refilled successfully.\n";
}

void VendingMachine::viewReports() {
    reportManager->displayReports();
}
*/
