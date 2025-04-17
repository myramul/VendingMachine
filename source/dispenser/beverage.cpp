#include "dispenser/beverage.h"

Beverage::Beverage() : beverageName("Unnamed Beverage") {}

Beverage::Beverage(const std::string& name) : beverageName(name) {}

void Beverage::setName(const std::string& name) {
    beverageName = name;
}

std::string Beverage::getName() const {
    return beverageName;
}
