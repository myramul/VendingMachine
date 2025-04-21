#ifndef DISPENSER_CONTAINER_H
#define DISPENSER_CONTAINER_H

#include <vector>
#include <string>
#include "dispenser/slot.h"
#include "dispenser/beverage.h"
#include "dispenser/dispenser_container_io.h"
#include "event/event_manager.h"

enum class DispenserState {
    Idle,
    Processing,
    Maintenance
}; // MAKE CHANGES TO IMPLEMENTATION BASED ON THIS . STATE IS NOT A STRING

class DispenserContainer {
private:
    std::vector<Slot> storage;
    std::string bin;
    DispenserState state;
    Beverage selectedBeverage;
    EventManager* eventManager;
    DispenserContainerIO* io;
    double insertedAmount = 0.0;

public:
    DispenserContainer(EventManager* manager, DispenserContainerIO* io);

    void selectBeverage();
    void dispenseBeverage(const Beverage& beverage);
    void onRefillBeverages();
    void setState(DispenserState newState);  
    void onSufficientFunds(EventData data);
    void notifyGiveChange();

    bool enterMaintenanceMode();
    bool enterProcessingMode();
    bool enterIdleMode();

    void setDispensedBeverage();
    void collectItem();

    std::string getState() const;
};

#endif // DISPENSER_CONTAINER_H

