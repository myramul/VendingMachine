#include "dispenser/dispenser_container_io.h"
#include <iostream>

class ConsoleDispenserContainerIO : public DispenserContainerIO {
public:
    void displayMenu() override {
        // THIS IS SUPPOSED TO BE THE MENU OF BEVERAGES NOT OF THE ENTIRE MACHINE
        // IT'S SUPPOSED TO BE LIKE:
        // [1] Coke $1.00 [2] Pepsi $1.00 [3] Sprite $1.00
        // [4] Water $1.00 [5] Juice $1.00 etc... based on the price of each slot
        // if a slot is unavailable, display it as [X] Coke $1.00 and the user can not select it
        // here you loop through each slot to display the beverage in the front and the price of it
        // you might have to pass the storage as a parameter to this function
        std::cout << "==== VENDING MACHINE MENU ====\n";
        std::cout << "1. Select Beverage\n";
        std::cout << "2. Maintenance Mode\n";
        std::cout << "3. Exit\n";
    }

    void handleSelectionInput() override {
        // SEE COMMENT ON MENU AND CHANGE THIS FUNCTION BASED ON THAT
        // THIS IS THE USER SELECTING A BEVERAGE FROM THE MENU
        std::cout << "Please enter your selection (1-3): ";
        int selection;
        std::cin >> selection;
        std::cout << "You selected option " << selection << ".\n";
    }

    void displaySelectedBeverage() override {
        std::cout << "Your beverage has been selected.\n";
        // PRINT THE NAME AND PRICE OF THE SELECTED BEVERAGE USING THE BEVERAGE IO HERE
    }

    void displayDispensedBeverage() override {
        std::cout << "Dispensing your beverage. Please wait...\n";
        // PRINT THE NAME OF THE BEVERAGE BEING DISPENSED
    }

    void displaySlotValues() override {
        std::cout << "Displaying all slot values...\n";
        // loop over slots here if connected to a container
        // THIS FUNCTION WILL BE CALLED BY DISPLAY MENU 
    }

    void inputRefillBeverages() override {
        std::cout << "Enter new beverage details to refill the slots.\n";
        // refill logic
        // ADD IN THE MAINTENNACE PERSON CAN ADD ONE BEVERAGE AT A TIME TO A SLOT
        // THE MAINTENACE PERSON PICKS A SLOT AND THEN PUTS IN BEVERAGES ONE AT A TIME 
        // UNTIL THEY CANCEL OR THE SLOT IS FULL AND THEN THEY PICK A DIFFERENT SLOT AND SO ON
        // YOU WILL HAVE TO CALL THE SLOT REFILL FUNCTION HERE and ALSO GET THE SLOT MAX CAPACITY
    }
};
