#include "vending_machine/vending_machine_io.h"
#include "vending_machine/vending_machine.h"
#include <iostream>
#include <string>

VendingMachineIO::VendingMachineIO(VendingMachine* machine)
    : vendingMachine(machine) {}

void VendingMachineIO::displayWelcomeMessage() {
    std::cout << "Welcome to Bug Busters Vending Machine!\n";
    std::cout << "We accept: Nickels ($0.05), Dimes ($0.10) and Quarters ($0.25).\n";
    std::cout << "Available Beverages:\n";
    // for now:
    std::cout << "1. Cola - $1.00\n";
    std::cout << "2. Water - $0.75\n";
    std::cout << "3. Juice - $1.25\n";
    std::cout << "Press [Enter] to continue or type maintenance password:\n";

    std::string input;
    std::getline(std::cin, input);

    if (vendingMachine->authenticateMaintenancePasscode(input)) {
        vendingMachine->enterMaintenanceMode();
        displayMaintenanceMenu();
        handleMaintenanceMenuSelection();
    } else {
        std::cout << "Starting normal transaction...\n";
        vendingMachine->enterProcessingMode();
    }
}

void VendingMachineIO::displayMaintenanceMenu() {
    std::cout << "=== Maintenance Menu ===\n";
    std::cout << "1. Collect Money\n";
    std::cout << "2. Refill Change\n";
    std::cout << "3. Refill Beverages\n";
    std::cout << "4. View Reports\n";
    std::cout << "5. Exit Maintenance Mode\n";
}

void VendingMachineIO::handleMaintenanceMenuSelection() {
    int choice = 0;
    do {
        std::cout << "\nEnter an option number: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the buffer after reading int input

        switch (choice) {
            case 1:
                vendingMachine->collectMoney();
                break;
            case 2:
                vendingMachine->refillChange();
                break;
            case 3:
                vendingMachine->refillBeverages();
                break;
            case 4:
                vendingMachine->viewReports();
                break;
            case 5:
                vendingMachine->lockMachine();
                vendingMachine->enterIdleMode();
                std::cout << "Exiting maintenance mode.\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);
}
