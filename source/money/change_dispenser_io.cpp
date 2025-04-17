// change_dispenser_io.cpp
#include "money/change_dispenser_io.h"
#include "money/change_dispenser.h"
#include <iomanip>

ChangeDispenserIO::ChangeDispenserIO(ChangeDispenser* owner) : changeDispenser(owner) {}

void ChangeDispenserIO::displayReturnedChange(double value) {
    if (value == 0.0) {
        std::cout << "Returning no change." << std::endl;
        return;
    }
    std::cout << "Returning change: $" <<  std::fixed << std::setprecision(2) << value << std::endl;
}
