#ifndef SLOT_H
#define SLOT_H

#include <vector>
#include <string>
#include "dispenser/beverage.h"

class Slot {
private:
    int slotID;
    std::vector<Beverage> beverages;
    double price;
    std::string state;
    int maxCapacity;

public:
    Slot(int id, double price, int capacity);

    int getID() const;
    std::vector<Beverage> getBeverages() const;
    double getPrice() const;
    std::string getState() const;
    int getCurrentCount() const;

    void setState(const std::string& newState);
    bool fillBeverage(const Beverage& bev);
    Beverage getFrontBeverage() const;
    bool isSlotAvailable() const;
};

#endif // SLOT_H
