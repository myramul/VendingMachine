#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <string>
#include "dispenser/dispenser_container.h"
#include "money/money_handler.h"
#include "event/event_manager.h"
#include "report/report_manager.h"
#include "vending machine/vendingmachine_io.h"

class VendingMachine {
private:
    DispenserContainer* dispenserComponent;
    MoneyHandler* moneyComponent;
    EventManager* eventManager;
    ReportManager* reportManager;
    std::string state; // "Idle", "Maintenance", "Processing"
    std::string maintenancePassword;

public:
    VendingMachine(const std::string& password);

    void setState(const std::string& newState);
    void enterMaintenanceMode();
    bool unlockMachine(const std::string& inputPassword);
    void lockMachine();
    void enterIdleMode();
    void enterProcessingMode();
    void initializeMachine();
    bool authenticateMaintenancePasscode(const std::string& inputPasscode);
    void onTransactionComplete();
};

#endif
