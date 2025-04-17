#include "dispenser/beverage_io.h"

void BeverageIO::displayBeverage(const Beverage& beverage) {
    std::cout << "Selected Beverage: " << beverage.getName() << std::endl;
}
