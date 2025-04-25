#include "dispenser/dispenser_bin.h"

void DispenserBin::placeBeverage(const Beverage& beverage) {
    if (currentBeverage.has_value()) {
        std::cout << "Bin is full! Please collect your beverage before dispensing a new one.\n";
        return;
    }
    currentBeverage = beverage;
    std::cout << beverage.getName() << " is now in the bin. Please collect it.\n";
}

bool DispenserBin::isOccupied() const {
    return currentBeverage.has_value();
}

void DispenserBin::collectBeverage() {
    if (currentBeverage.has_value()) {
        std::cout << "You collected: " << currentBeverage->getName() << "\n";
        currentBeverage.reset();
    } else {
        std::cout << "The bin is empty. Nothing to collect.\n";
    }
}
