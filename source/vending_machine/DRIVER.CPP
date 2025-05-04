#include <iostream>
#include "vending_machine/vending_machine.h"
#include "vending_machine/vending_machine_io.h"

#include "event/event_manager.h"
#include "report/report_manager.h"

#include "money/coin_slot.h" 
#include "money/coin_slot_io.h"
#include "money/collected_coin.h"
#include "money/collected_coin_io.h"
#include "money/coin_storage.h"
#include "money/coin.h"
#include "money/coin_io.h"
#include "money/change_drawer.h"
#include "money/change_drawer_io.h"
#include "money/change_dispenser.h"
#include "money/change_dispenser_io.h"
#include "money/coin_return.h"
#include "money/coin_return_io.h"
#include "money/money_handler.h"

#include "dispenser/slot.h"
#include "dispenser/slot_io.h"
#include "dispenser/beverage.h"
#include "dispenser/beverage_io.h"
#include "dispenser/dispenser_container.h"
#include "dispenser/dispenser_bin.h"
#include "dispenser/dispenser_container_io.h"

/* BULD COMMAND FOR G++ compiler

g++ -Iheader \
  source/vending_machine/vending_machine.cpp \
  source/vending_machine/vending_machine_io.cpp \
  source/event/event_manager.cpp \
  source/report/report_manager.cpp \
  source/money/coin_slot.cpp \
  source/money/coin_slot_io.cpp \
  source/money/collected_coin.cpp \
  source/money/coin_storage.cpp \
  source/money/coin.cpp \
  source/money/coin_io.cpp \
  source/money/collected_coin_io.cpp \
  source/money/change_drawer.cpp \
  source/money/change_dispenser.cpp \
  source/money/change_drawer_io.cpp \
  source/money/change_dispenser_io.cpp \
  source/money/coin_return.cpp \
  source/money/coin_return_io.cpp \
  source/money/money_handler.cpp \
  source/dispenser/slot.cpp \
  source/dispenser/slot_io.cpp \
  source/dispenser/beverage.cpp \
  source/dispenser/beverage_io.cpp \
  source/dispenser/dispenser_container.cpp \
  source/dispenser/dispenser_bin.cpp \
  source/dispenser/dispenser_container_io.cpp \
  source/vending_machine/driver.cpp \
  -std=c++20 \
  -o vm_test_driver
*/



int main(){
    // CREATING EVENT MANAGER
    EventManager eventManager;

    // CREATING REPORT MANAGER
    ReportManager reportManager;

    // CREATING MONEY
    CollectedCoin collectedCoin(&eventManager);
    CoinReturn coinReturn(&eventManager);
    CoinSlot coinSlot(&eventManager, &collectedCoin, 1.00, &coinReturn);
    ChangeDrawer changeDrawer(&eventManager);
    ChangeDispenser changeDispenser(&eventManager, &changeDrawer);
    MoneyHandler moneyHandler(&collectedCoin, &coinSlot, &changeDrawer, &changeDispenser, &eventManager, &coinReturn);

    // CREATING DISPENSER
    DispenserContainer dispenserContainer(&eventManager);
  
    // CREATING VENDING MACHINE
    std::string maintenance_password = "hello";

   VendingMachine vendingMachine(
    maintenance_password, 
    &eventManager, 
    &moneyHandler, 
    &dispenserContainer, 
    &reportManager
  );
   

    // RUNNING VM
    vendingMachine.startMachine();


    return 0;
}