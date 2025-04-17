#ifndef BEVERAGE_IO_H
#define BEVERAGE_IO_H

#include "Beverage.h"

class BeverageIO {
public:
    virtual void displayBeverage(const Beverage& beverage) = 0;
    virtual ~BeverageIO() = default;
};

#endif // BEVERAGE_IO_H
