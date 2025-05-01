#include "dispenser/dispenser_container_io.h"
#include <iostream>

class ConsoleDispenserContainerIO : public DispenserContainerIO {
public:

    void displayMenu(const std::vector<Slot>& storage) override {
        std::cout << "==== BEVERAGE MENU ====\n";
        int optionNumber = 1;
        for (const auto& slot : storage) {
            std::cout << "[";
            if (slot.getCurrentCount() == 0) {
                std::cout << "X";
            } else {
                std::cout << optionNumber;
            }
            std::cout << "] " << slot.getFrontBeverage().getName() << " $" << slot.getPrice() << "\n";
            optionNumber++;
        }
    }

    int handleSelectionInput(const std::vector<Slot>& storage) override {
        // THIS SHOULD BE A LOOP:
            // IF THE CUSTIMER CHOSOES AN INVALID SLOT, DISPLAY THE MESSAGE
            // AND THEN ALLOW THEM TO ENTER ANOTHER SELCTION UNTIL THEY PICK A VALID SLOT
            // ONLY THEN RETURN THE INDEX OF THE CHOSEN SLOT 
        int selection;
        std::cout << "Please enter your selection number: ";
        std::cin >> selection;

        if (selection <= 0 || selection > storage.size()) {
            std::cout << "Invalid selection.\n";
            return -1;
        }

        const Slot& chosenSlot = storage[selection - 1];
        if (chosenSlot.getCurrentCount() == 0) {
            std::cout << "Selected slot is empty!\n";
            return -1;
        }

        std::cout << "You selected: " << chosenSlot.getFrontBeverage().getName() << "\n";
        return selection - 1;  // Return index of slot
    }

    void displaySelectedBeverage(const Beverage& beverage, double price) override {
        std::cout << "You selected: " << beverage.getName() << " - Price: $" << price << "\n";
    }
    

    void displayDispensedBeverage(const Beverage& beverage) override {
        std::cout << "Dispensing: " << beverage.getName() << "\n";
    }

    void displaySlotValues(const std::vector<Slot>& storage) override {
        std::cout << "==== SLOT DETAILS ====\n";
        for (const auto& slot : storage) {
            std::cout << "Slot [" << slot.getID() << "] - "
                      << slot.getFrontBeverage().getName() << " | Price: $" << slot.getPrice()
                      << " | Quantity: " << slot.getCurrentCount() << "\n";
        }
    }

    void inputRefillBeverages(std::vector<Slot>& storage) override {
        int slotId;
        std::string beverageName;

        while (true) {
            std::cout << "Enter Slot Number to refill (or -1 to exit): ";
            std::cin >> slotId;
            if (slotId == -1) break;

            if (slotId <= 0 || slotId > storage.size()) {
                std::cout << "Invalid slot number.\n";
                continue;
            }

            Slot& slot = storage[slotId - 1];
            while (slot.isSlotAvailable()) {
                std::cout << "Enter beverage name to add (or type 'cancel' to stop): ";
                std::cin >> beverageName;
                if (beverageName == "cancel") break;

                if (slot.fillBeverage(Beverage(beverageName))) {
                    std::cout << "Added " << beverageName << " to Slot " << slotId << "\n";
                } else {
                    std::cout << "Slot is full!\n";
                    break;
                }
            }
        }
    }
};

