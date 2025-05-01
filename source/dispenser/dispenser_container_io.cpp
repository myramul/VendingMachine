#include "dispenser/dispenser_container_io.h"
#include <iostream>

DispenserContainerIO::DispenserContainerIO(DispenserContainer* owner) : owner(owner) {}

void DispenserContainerIO::displayMenu(const std::vector<Slot>& storage) {
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

int DispenserContainerIO::handleSelectionInput(const std::vector<Slot>& storage) {
        // THIS SHOULD BE A LOOP:
            // IF THE CUSTOMER CHOSOES AN INVALID SLOT, DISPLAY THE MESSAGE
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

void DispenserContainerIO::displaySelectedBeverage(const Beverage& beverage, double price)  {
        std::cout << "You selected: " << beverage.getName() << " - Price: $" << price << "\n";
    }
    

void DispenserContainerIO::displayDispensedBeverage(const Beverage& beverage)  {
        std::cout << "Dispensing: " << beverage.getName() << "\n";
    }

void DispenserContainerIO::displaySlotValues(const std::vector<Slot>& storage)  {
        std::cout << "==== SLOT DETAILS ====\n";
        for (const auto& slot : storage) {
            std::cout << "Slot [" << slot.getID() << "] - "
                      << slot.getFrontBeverage().getName() << " | Price: $" << slot.getPrice()
                      << " | Quantity: " << slot.getCurrentCount() << "\n";
        }
    }

void DispenserContainerIO::inputRefillBeverages(std::vector<Slot>& storage)  {
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

