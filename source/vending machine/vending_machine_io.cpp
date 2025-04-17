#include "vending machine/vending_machine_io.h"
#include <iostream>

void VendingMachineIO::displayWelcomeMessage() {
    std::cout << "Welcome to Bug Busters Vending Machine!\n";
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
    std::cout << "Enter an option number: ";
    int choice;
    std::cin >> choice;
    // For this prototype, we'll just echo the selection
    std::cout << "You selected option " << choice << ".\n";
}
