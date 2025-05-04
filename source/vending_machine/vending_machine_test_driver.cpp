// vending_machine_test_driver.cpp
// nodira kazakova
/*

#include <iostream>
#include <string>
#include "vending_machine/vending_machine.h"
#include "vending_machine/vending_machine_io.h"
#include "event/event_manager.h"


class MockDispenserContainerIO : public DispenserContainerIO {
public:
    void displayMenu(const std::vector<Slot>&) override {
        std::cout << "[Mock] Displaying menu\n";
    }

    int handleSelectionInput(const std::vector<Slot>&) override {
        std::cout << "[Mock] Handling selection input\n";
        return 0; // Simulate selecting the first slot
    }

    void displaySelectedBeverage(const Beverage&, double) override {
        std::cout << "[Mock] Displaying selected beverage\n";
    }

    void displayDispensedBeverage(const Beverage&) override {
        std::cout << "[Mock] Displaying dispensed beverage\n";
    }

    void displaySlotValues(const std::vector<Slot>&) override {
        std::cout << "[Mock] Displaying slot values\n";
    }

    void inputRefillBeverages(std::vector<Slot>&) override {
        std::cout << "[Mock] Refilling beverages\n";
    }
};



// Mock components to isolate VendingMachine logic
class MockMoneyHandler : public MoneyHandler {
public:
    MockMoneyHandler() : MoneyHandler(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr) {}
    void collectMoney() {
        std::cout << "[Mock] Money collected.\n";
    }
    void refillChange() {
        std::cout << "[Mock] Change refilled.\n";
    }
};

class MockDispenserContainer : public DispenserContainer {
public:
    MockDispenserContainer() : DispenserContainer(nullptr, nullptr) {}

    void refillAll() {
        std::cout << "[Mock] Beverages refilled.\n";
    }
};

class MockReportManager : public ReportManager {
public:
    void displayReports() {
        std::cout << "[Mock] Displaying report summary.\n";
    }
};

int main() {
    std::cout << "==== VENDING MACHINE TEST DRIVER ====\n";

    // Set up EventManager
    EventManager eventManager;

    // Mock components
    auto moneyHandler = new MockMoneyHandler();
    MockDispenserContainerIO* mockIO = new MockDispenserContainerIO();
    DispenserContainer* dispenser = new DispenserContainer(&eventManager, mockIO);
    auto reports = new MockReportManager();

    // Set test password
    std::string password = "admin123";

    // Create VendingMachine
    VendingMachine machine(password, &eventManager, moneyHandler, dispenser, reports);
    VendingMachineIO machineIO(&machine);

    // ==== TEST CASES ====

    std::cout << "\nInitialize Machine...\n";
    machine.initializeMachine();

    std::cout << "\nInvalid Maintenance Password...\n";
    if (machine.unlockMachine("wrongpass")) {
        std::cerr << "Should not unlock with wrong password.\n";
    }
    else {
        std::cout << "Correctly rejected wrong password.\n";
    }

    std::cout << "\nValid Maintenance Password and Menu Actions...\n";
    if (machine.unlockMachine("admin123")) {
        machine.enterMaintenanceMode();

        // Simulate user choosing options
        std::cout << "\n--- Simulate Maintenance Menu Actions ---\n";
        machine.collectMoney();     // Case 1
        machine.refillChange();     // Case 2
        machine.refillBeverages();  // Case 3
        machine.viewReports();      // Case 4

        std::cout << "\nExiting Maintenance Mode...\n";
        machine.lockMachine();
        if (machine.unlockMachine("admin123")) {
            std::cout << "Still accepts valid password after lock.\n";
        }
    }
    else {
        std::cerr << "Valid password rejected.\n";
    }

    std::cout << "\nTransaction Complete Event...\n";
    eventManager.notify(EventType::TransactionComplete, EventData{ "Purchase complete" });
    // Should print that the machine goes to idle

    machineIO.displayWelcomeMessage();

    std::cout << "\n==== ALL TESTS DONE ====\n";

    // Clean up (if needed)
    delete moneyHandler;
    delete dispenser;
    delete reports;

    return 0;
}
*/