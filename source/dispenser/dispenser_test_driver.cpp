#include <iostream>
#include "dispenser/slot.h"
#include "dispenser/slot_io.h"
#include "dispenser/beverage.h"
#include "dispenser/beverage_io.h"
#include "dispenser/dispenser_container.h"
#include "dispenser/dispenser_bin.h"
#include "dispenser/dispenser_container_io.h"
#include "event/event_manager.h"

/*

g++ -Iheader source/dispenser/slot.cpp source/dispenser/slot_io.cpp source/dispenser/beverage.cpp source/dispenser/beverage_io.cpp source/dispenser/dispenser_container.cpp source/dispenser/dispenser_container_io.cpp source/dispenser/dispenser_bin.cpp source/event/event_manager.cpp source/dispenser/dispenser_test_driver.cpp -std=c++20
*/
int main(){
    // DispenserContainer(EventManager* manager;
    EventManager manager;
    DispenserContainer dispenserContainer(&manager);
}