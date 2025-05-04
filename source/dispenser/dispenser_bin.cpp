#include "dispenser/dispenser_bin.h"

bool DispenserBin::placeBeverage(const Beverage& beverage) {
    /*
    if (currentBeverage.has_value()) {
        std::cout << "Bin is full! Please collect your beverage before dispensing a new one.\n";
        return;
    }
    */
    currentBeverage = beverage;

    std::cout << beverage.getName() << " is now in the bin. Please collect it by typing 'collect'.\n";
    while (true) {
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    if (input == "collect") {
        collectBeverage();
        return true;
    } else {
        std::cout << "Invalid input. Please type 'collect' to collect the beverage.\n";
    }
}
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
