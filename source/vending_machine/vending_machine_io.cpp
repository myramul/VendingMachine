// vending_machine_io.cpp
// nodira kazakova

#include "vending_machine/vending_machine_io.h"
#include "vending_machine/vending_machine.h"
#include <iostream>
#include <string>
#include <limits>


VendingMachineIO::VendingMachineIO(VendingMachine* machine)
    : vendingMachine(machine) {}

void VendingMachineIO::displayWelcomeMessage() {
    std::cout << "\nWelcome to Bug Busters Vending Machine!\n";
    std::cout << "We accept: Nickels ($0.05), Dimes ($0.10) and Quarters ($0.25).\n";

    vendingMachine->displayMenu();
    std::cout << "\nPress [Enter] to buy a beverage \n(Or type maintenance password):\n";

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    if (vendingMachine->authenticateMaintenancePasscode(input)) {
        vendingMachine->enterMaintenanceMode();
        displayMaintenanceMenu();
        handleMaintenanceMenuSelection();
    }
    else {
        std::cout << "\nStarting normal transaction...\n";
        vendingMachine->enterProcessingMode();
    }
}

void VendingMachineIO::displayMaintenanceMenu() {
    std::cout << "\n=== Maintenance Menu ===\n";
    std::cout << "1. Collect Money\n";
    std::cout << "2. Refill Change\n";
    std::cout << "3. Refill Beverages\n";
    std::cout << "4. View Transaction Log Report\n";
    std::cout << "5. Exit Maintenance Mode\n";
}

void VendingMachineIO::handleMaintenanceMenuSelection() {
    int choice = 0;
    do {
        std::cout << "\nEnter an option number: ";
        std::cin >> choice;
        std::cin.ignore(); 

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
            std::cout << "Exiting maintenance mode.\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 5);
}
