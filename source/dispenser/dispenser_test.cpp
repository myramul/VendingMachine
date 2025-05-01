#include <iostream>
#include <memory>

#include "dispenser/dispenser_container.h"
#include "dispenser/dispenser_container_io.h"
#include "dispenser/slot.h"
#include "dispenser/slot_io.h"
#include "event/event_manager.h"

// Using the Console I/O implementation
class ConsoleDispenserContainerIO : public DispenserContainerIO {
public:
    void displayMenu(const std::vector<Slot>& storage) override {
        std::cout << "\n==== BEVERAGE MENU ====\n";
        int option = 1;
        for (const auto& slot : storage) {
            std::cout << "[" << (slot.getCurrentCount() > 0 ? std::to_string(option) : "X") << "] "
                      << slot.getFrontBeverage().getName() << " - $" << slot.getPrice() << "\n";
            option++;
        }
    }

    int handleSelectionInput(const std::vector<Slot>& storage) override {
        int selection;
        std::cout << "\nEnter selection number: ";
        std::cin >> selection;

        if (selection <= 0 || selection > storage.size()) return -1;
        const Slot& chosen = storage[selection - 1];
        if (chosen.isEmpty()) return -1;

        return selection - 1;
    }

    void displaySelectedBeverage(const Beverage& beverage, double price) override {
        std::cout << "Selected: " << beverage.getName() << " | Price: $" << price << "\n";
    }

    void displayDispensedBeverage(const Beverage& beverage) override {
        std::cout << "Dispensing: " << beverage.getName() << "\n";
    }

    void displaySlotValues(const std::vector<Slot>& storage) override {
        std::cout << "\n==== SLOT INVENTORY ====\n";
        for (const auto& slot : storage) {
            std::cout << "Slot [" << slot.getID() << "] - "
                      << slot.getFrontBeverage().getName() << ", Qty: " << slot.getCurrentCount()
                      << ", Price: $" << slot.getPrice() << "\n";
        }
    }

    void inputRefillBeverages(std::vector<Slot>& storage) override {
        std::cout << "\n==== REFILLING SLOTS ====\n";
        for (auto& slot : storage) {
            std::string input;
            while (slot.isSlotAvailable()) {
                std::cout << "Add beverage to Slot " << slot.getID() << " (or 'stop'): ";
                std::cin >> input;
                if (input == "stop") break;
                slot.fillBeverage(Beverage(input));
            }
        }
    }
};

void setupSlots(std::vector<Slot>& storage) {
    Slot s1(1, 1.25, 5);
    Slot s2(2, 1.00, 5);
    Slot s3(3, 0.75, 5);

    s1.fillBeverage(Beverage("Coke"));
    s1.fillBeverage(Beverage("Coke"));

    s2.fillBeverage(Beverage("Pepsi"));
    s2.fillBeverage(Beverage("Pepsi"));

    s3.fillBeverage(Beverage("Water"));
    s3.fillBeverage(Beverage("Water"));

    storage.push_back(s1);
    storage.push_back(s2);
    storage.push_back(s3);
}

int main() {
    std::cout << "=== DISPENSER COMPONENT TEST ===\n";

    EventManager eventManager;
    ConsoleDispenserContainerIO io;

    DispenserContainer dispenser(&eventManager, &io);
    setupSlots(dispenser.getStorage()); // Direct slot initialization for test purposes

    std::cout << "\n--- Current Slot Inventory ---\n";
    io.displaySlotValues(dispenser.getStorage());

    // Simulate FundsAvailable event to trigger selection & dispensing
    EventData funds;
    funds.inserted_amount = 1.25;
    eventManager.notify(EventType::FundsAvailable, funds);

    // Simulate collecting beverage
    dispenser.collectItem();

    std::cout << "\n--- Final Slot Inventory ---\n";
    io.displaySlotValues(dispenser.getStorage());

    return 0;
}
