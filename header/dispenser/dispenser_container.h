#ifndef DISPENSER_CONTAINER_H
#define DISPENSER_CONTAINER_H

#include <vector>
#include <string>
#include "dispenser/slot.h"
#include "dispenser/beverage.h"
#include "dispenser/dispenser_container_io.h"

class EventManager; // Forward declaration

class DispenserContainer {
private:
    std::vector<Slot> storage;
    std::string bin;
    std::string state;
    Beverage selectedBeverage;
    EventManager* eventManager;
    DispenserContainerIO* io;

public:
    DispenserContainer(EventManager* manager, DispenserContainerIO* io);

    void selectBeverage();
    void dispenseBeverage(const Beverage& beverage);
    void onRefillBeverages();
    void setState(const std::string& newState);
    void onSufficientFunds();
    void notifyGiveChange();

    bool enterMaintenanceMode();
    bool enterProcessingMode();
    bool enterIdleMode();

    void setDispensedBeverage();
    void collectItem();

    std::string getState() const;
};

#endif // DISPENSER_CONTAINER_H
