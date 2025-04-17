#ifndef DISPENSER_CONTAINER_IO_H
#define DISPENSER_CONTAINER_IO_H

class DispenserContainerIO {
public:
    virtual void displayMenu() = 0;
    virtual void handleSelectionInput() = 0;
    virtual void displaySelectedBeverage() = 0;
    virtual void displayDispensedBeverage() = 0;
    virtual void displaySlotValues() = 0;
    virtual void inputRefillBeverages() = 0;

    virtual ~DispenserContainerIO() = default;
};

#endif // DISPENSER_CONTAINER_IO_H
