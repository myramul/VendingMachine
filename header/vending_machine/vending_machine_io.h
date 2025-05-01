#ifndef VENDING_MACHINE_IO_H
#define VENDING_MACHINE_IO_H

class VendingMachine; // Forward declare

class VendingMachineIO {
private:
    VendingMachine* vendingMachine;

public:
    VendingMachineIO(VendingMachine* machine);

    void displayWelcomeMessage();
    void displayMaintenanceMenu();
    void handleMaintenanceMenuSelection();
};

#endif
