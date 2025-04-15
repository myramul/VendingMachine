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

void ChangeDrawer::onRefllChange() {
    std::string name;
    int quantity;
    std::cout << "Enter coin name (NICKEL, DIME, QUARTER): ";
    std::cin >> name;
    std::cout << "Enter quantity to add: ";
    std::cin >> quantity;
    refill_slot(name, quantity);
}

void ChangeDrawer::refill_slot(std::string name, int quantity) {
    int current = coin_storage[name];
    int max = max_capacity_slot[name];
    int to_add = std::min(quantity, max - current);
    coin_storage[name] += to_add;
    std::cout << "Added " << to_add << " " << name << "s to change drawer.\n";
}

void ChangeDrawer::displayChangeLevels() {
    io.displayChangeLevels(coin_storage);
}