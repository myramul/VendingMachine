// Change dispenser io H

#ifndef CHANGE_DISPENSER_IO_H
#define CHANGE_DISPENSER_IO_H

#include <iostream>

class ChangeDispenser;

class ChangeDispenserIO {
    public:
        void displayReturnedChange(double value);
        ChangeDispenserIO(ChangeDispenser* owner);
    private:
        ChangeDispenser* changeDispenser;
};

#endif