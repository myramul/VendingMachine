// change drawer cpp

#include "money/change_drawer.h"

ChangeDrawer::ChangeDrawer(EventManager* eventManager, std::unordered_map<std::string, int> max_capacity) : eventManager(eventManager), io(this), max_capacity_slot(max_capacity) {}
ChangeDrawer::ChangeDrawer(EventManager* eventManager) : eventManager(eventManager), io(this) {
    // testing purposes
    coin_storage = {{"QUARTER", 12}, {"DIME", 20}, {"NICKEL", 15}};
}

double ChangeDrawer::getTotalChange() {
    return calculate_total_value();
}

void ChangeDrawer::onRefillChange() {
    std::cout << "REFILL CHANGE DRAWER" << std::endl;
    std::string name;
    int quantity;
    while (true) {
        std::cout << "Enter coin name (NICKEL, DIME, QUARTER) or 'X' to finish: ";
        std::cin >> name;
        if (name == "X" || name == "x") {
            break;
        }
        std::cout << "Enter quantity to add: ";
        std::cin >> quantity;
        Coin coin(name);
        if (coin.isValidCoin(name)) {
            refill_slot(coin.getName(), quantity);
        }else{
            std::cout << "Invalid coin name." << std::endl;
        }
    }
    displayChangeLevels();
}

void ChangeDrawer::refill_slot(std::string name, int quantity) {
    int current = coin_storage[name];
    int max = max_capacity_slot[name];
    int to_add = std::min(quantity, max - current);
    coin_storage[name] += to_add;
    std::cout << "Added " << to_add << " " << name << "s to change drawer.\n";
    if (quantity + current > max) {
        std::cout << "Warning: Change drawer is full for " << name << "s.\n" << "Returning " << quantity - to_add << " " << name << "s.\n";
    }
}

void ChangeDrawer::displayChangeLevels() {
    io.displayChangeLevels(coin_storage);
}