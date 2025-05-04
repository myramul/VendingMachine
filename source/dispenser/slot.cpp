#include "dispenser/slot.h"

Slot::Slot(int id, double price, int capacity)
    : slotID(id), price(price), state("Inactive"), maxCapacity(capacity) {}

// testing constructor
Slot::Slot(int id, double price, int capacity, std::vector<Beverage> beverages) 
: slotID(id), price(price), maxCapacity(capacity), beverages(beverages){}

int Slot::getID() const {
    return slotID;
}

std::vector<Beverage> Slot::getBeverages() const {
    return beverages;
}

double Slot::getPrice() const {
    return price;
}

std::string Slot::getState() const {
    return state;
}

int Slot::getCurrentCount() const {
    return beverages.size();
}

void Slot::setState(const std::string& newState) {
    state = newState;
}

bool Slot::fillBeverage(const Beverage& bev) {
    if (beverages.size() < maxCapacity) {
        beverages.push_back(bev);
        return true;
    }
    return false;
}

Beverage Slot::getFrontBeverage() const {
    if (!beverages.empty()) {
        return beverages.front();
    }
    return Beverage("No Beverage");
}

bool Slot::isSlotAvailable() const {
    return beverages.size() < maxCapacity;
}


bool Slot::popFrontBeverage() {
    if (!beverages.empty()) {
        beverages.erase(beverages.begin());
        return true;
    }
    return false;
}

bool Slot::isEmpty() const {
    return beverages.empty();
}
