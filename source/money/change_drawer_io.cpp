
// change_drawer_io.cpp
#include "money/change_drawer_io.h"
#include "money/change_drawer.h"
#include <iomanip>

void ChangeDrawerIO::inputChangeCoins() {
    std::string name;
    int quantity;

    std::cout << "\nEnter coin name to refill (NICKEL, DIME, QUARTER): ";
    std::cin >> name;
    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    if (changeDrawer) {
        changeDrawer->refill_slot(name, quantity);
    } else {
        std::cout << "Error: ChangeDrawer is not set.\n";
    }
}

void ChangeDrawerIO::displayChangeLevels(std::unordered_map<std::string, int> levels) const {
    std::cout << "\nCurrent Change Levels:\n";
    for (const auto& [coin, amount] : levels) {
        std::cout << " - " << coin << ": x" << amount << std::endl;
    }
    std::cout << "Total Change: $" << std::fixed << std::setprecision(2) << changeDrawer->getTotalChange() << std::endl;
}

