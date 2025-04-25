#ifndef DISPENSER_CONTAINER_IO_H
#define DISPENSER_CONTAINER_IO_H

#include <vector>
#include "dispenser/slot.h"

class DispenserContainerIO {
public:
    virtual void displayMenu(const std::vector<Slot>& storage) = 0;
    virtual int handleSelectionInput(const std::vector<Slot>& storage) = 0;
    virtual void displaySelectedBeverage(const Beverage& beverage, double price) = 0;
    virtual void displayDispensedBeverage(const Beverage& beverage) = 0;
    virtual void displaySlotValues(const std::vector<Slot>& storage) = 0;
    virtual void inputRefillBeverages(std::vector<Slot>& storage) = 0;

    virtual ~DispenserContainerIO() = default;
};

#endif // DISPENSER_CONTAINER_IO_H
