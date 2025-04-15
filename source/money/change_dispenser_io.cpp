// change_dispenser_io.cpp
#include "money/change_dispenser_io.h"
#include "money/change_dispenser.h"

ChangeDispenserIO::ChangeDispenserIO(ChangeDispenser* owner) : changeDispenser(owner) {}

void ChangeDispenserIO::displayReturnedChange(double value) {
    std::cout << "Returning change: $" << value << std::endl;
}
