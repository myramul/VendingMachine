#ifndef DISPENSER_BIN_H
#define DISPENSER_BIN_H

#include "dispenser/beverage.h"
#include <optional>
#include <iostream>

class DispenserBin {
private:
    std::optional<Beverage> currentBeverage;

public:
    bool placeBeverage(const Beverage& beverage);
    bool isOccupied() const;
    void collectBeverage();
};

#endif // DISPENSER_BIN_H