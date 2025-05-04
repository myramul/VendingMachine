#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <string>
#include "dispenser/dispenser_container.h"
#include "money/money_handler.h"
#include "event/event_manager.h"
#include "report/report_manager.h"
#include "money/collected_coin.h"
#include "vending_machine/vending_machine_io.h"


enum class VendingMachineState {
    Idle,
    Processing,
    Maintenance
};

class VendingMachine {
private:
    DispenserContainer* dispenserComponent;
    MoneyHandler* moneyComponent;
    EventManager* eventManager;
    ReportManager* reportManager;
    VendingMachineState state;
    std::string maintenancePassword;
    VendingMachineIO io;

public:
    // Constructor with dependency injection
    VendingMachine(
        const std::string& password,
        EventManager* em,
        MoneyHandler* mh,
        DispenserContainer* dc,
        ReportManager* rm
    );

    // Core functions
    void setState(VendingMachineState newState);
    void enterMaintenanceMode();
    bool unlockMachine(const std::string& inputPassword);
    void lockMachine();
    void enterIdleMode();
    void enterProcessingMode();
    void initializeMachine();
    bool authenticateMaintenancePasscode(const std::string& inputPasscode);
    void onTransactionComplete(const EventData& data);
    void displayMenu();
    void startMachine();

    // New Maintenance Functions
    void collectMoney();
    void refillChange();
    void refillBeverages();
    void viewReports();
};

#endif
