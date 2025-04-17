#include "BeverageIO.h"

void BeverageIO::displayBeverage(const Beverage& beverage) {
    std::cout << "Selected Beverage: " << beverage.getName() << std::endl;
}
