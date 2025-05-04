#include "dispenser/dispenser_container_io.h"
#include <limits>
#include <iostream>

DispenserContainerIO::DispenserContainerIO(DispenserContainer* owner) : owner(owner) {}

void DispenserContainerIO::displayMenu(const std::vector<Slot>& storage) {
    
        std::cout << "==== BEVERAGE MENU ====\n";
        int optionNumber = 1;
        for (size_t i = 0; i < storage.size(); i += 2) {
            std::cout << "[" << (storage[i].getCurrentCount() == 0 ? "X" : std::to_string(optionNumber)) << "] " 
                      << storage[i].getFrontBeverage().getName() << " $" << storage[i].getPrice() << " | "
                      << "[" << (storage[i + 1].getCurrentCount() == 0 ? "X" : std::to_string(optionNumber + 1)) << "] " 
                      << storage[i + 1].getFrontBeverage().getName() << " $" << storage[i + 1].getPrice() << "\n";
            optionNumber += 2;
        }
}

int DispenserContainerIO::handleSelectionInput(const std::vector<Slot>& storage) {
    // converted to a loop so that it loops until the customer enters a valid selection
        int selection = -1;
    
        while (true) {
            std::cout << "Please enter your selection number: ";
            std::cin >> selection;
    
            if (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number.\n";
                continue;
            }
    
            if (selection <= 0 || selection > static_cast<int>(storage.size())) {
                std::cout << "Invalid selection. Please choose a number between 1 and " << storage.size() << ".\n";
                continue;
            }
    
            const Slot& chosenSlot = storage[selection - 1];
            if (chosenSlot.getCurrentCount() == 0) {
                std::cout << "Selected slot is empty! Please choose another.\n";
                continue;
            }
    
            return selection - 1;  
        }
}

void DispenserContainerIO::displaySelectedBeverage(const Beverage& beverage, double price)  {
        std::cout << "You selected: " << beverage.getName() << " Price: $" << price << "\n";
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

