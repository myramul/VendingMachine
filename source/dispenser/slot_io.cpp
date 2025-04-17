#include "dispenser/slot_io.h"

void SlotIO::displaySlot(const Slot& slot) {
    std::cout << "Slot ID: " << slot.getID() << std::endl;
    std::cout << "Price: $" << slot.getPrice() << std::endl;
    std::cout << "State: " << slot.getState() << std::endl;
    std::cout << "Beverages in slot: " << slot.getCurrentCount() << std::endl;

    std::vector<Beverage> bevs = slot.getBeverages();
    for (const auto& b : bevs) {
        std::cout << "- " << b.getName() << std::endl;
    }
}
