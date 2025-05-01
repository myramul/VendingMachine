#ifndef DISPENSER_CONTAINER_IO_H
#define DISPENSER_CONTAINER_IO_H

#include <vector>
#include "dispenser/slot.h"

class DispenserContainer;
class DispenserContainerIO {
public:
     void displayMenu(const std::vector<Slot>& storage);
     int handleSelectionInput(const std::vector<Slot>& storage);
     void displaySelectedBeverage(const Beverage& beverage, double price);
     void displayDispensedBeverage(const Beverage& beverage);
     void displaySlotValues(const std::vector<Slot>& storage);
     void inputRefillBeverages(std::vector<Slot>& storage);
     DispenserContainerIO(DispenserContainer* owner);
private:
     DispenserContainer* owner;

};

#endif // DISPENSER_CONTAINER_IO_H
