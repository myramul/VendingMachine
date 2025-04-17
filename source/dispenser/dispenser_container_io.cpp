#include "dispenser/dispenser_container_io.h"
#include <iostream>

class ConsoleDispenserContainerIO : public DispenserContainerIO {
public:
    void displayMenu() override {
        std::cout << "==== VENDING MACHINE MENU ====\n";
        std::cout << "1. Select Beverage\n";
        std::cout << "2. Maintenance Mode\n";
        std::cout << "3. Exit\n";
    }

    void handleSelectionInput() override {
        std::cout << "Please enter your selection (1-3): ";
        int selection;
        std::cin >> selection;
        std::cout << "You selected option " << selection << ".\n";
    }

    void displaySelectedBeverage() override {
        std::cout << "Your beverage has been selected.\n";
    }

    void displayDispensedBeverage() override {
        std::cout << "Dispensing your beverage. Please wait...\n";
    }

    void displaySlotValues() override {
        std::cout << "Displaying all slot values...\n";
        // loop over slots here if connected to a container
    }

    void inputRefillBeverages() override {
        std::cout << "Enter new beverage details to refill the slots.\n";
        // refill logic
    }
};
