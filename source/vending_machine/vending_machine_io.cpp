#include "vending_machine/vending_machine_io.h"
#include <iostream>

void VendingMachineIO::displayWelcomeMessage() {
    std::cout << "Welcome to Bug Busters Vending Machine!\n";
    // it should also say the coins it accepts and show the menu
    // it should be on stanby for input. maybe have a message press enter to continue
    // if the maintennace person types the passord it goes to maintennace mode
    // if the user types in enter it then tells the event manager to tell the coin slot to start accepting coins
    // by calling the function enterProcessingMode()
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
    // for each selection it should call the appropriate functions in the involved components
    // or maybe add a new event and then call the event manager and then it will call the appropriate functions
    // the second option might be easier
    std::cout << "Enter an option number: ";
    int choice;
    std::cin >> choice;
    // For this prototype, we'll just echo the selection
    std::cout << "You selected option " << choice << ".\n";
}
