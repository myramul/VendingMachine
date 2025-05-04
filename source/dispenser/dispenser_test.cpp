#include <iostream>

#include "dispenser/beverage.h"
#include "dispenser/slot.h"
#include "dispenser/dispenser_bin.h"
#include "dispenser/dispenser_container.h"
#include "event/event_manager.h"

// === BASIC TEST FUNCTIONS (NO ASSERT) ===

void test_beverage_class() {
    std::cout << "Testing Beverage class...\n";

    Beverage b1;
    std::cout << (b1.getName() == "Unnamed Beverage" ? "[PASS] Default name\n" : "[FAIL] Default name\n");

    Beverage b2("Cola");
    std::cout << (b2.getName() == "Cola" ? "[PASS] Parameter name\n" : "[FAIL] Parameter name\n");

    b2.setName("Sprite");
    std::cout << (b2.getName() == "Sprite" ? "[PASS] setName\n" : "[FAIL] setName\n");
}

void test_slot_class() {
    std::cout << "Testing Slot class...\n";

    Slot slot(1, 1.50, 2);
    Beverage b("Fanta");

    slot.fillBeverage(b);
    slot.fillBeverage(b);
    bool overfilled = !slot.fillBeverage(b); // Should be false

    std::cout << (overfilled ? "[PASS] Slot full correctly blocked\n" : "[FAIL] Slot overfilled\n");

    std::cout << (slot.getFrontBeverage().getName() == "Fanta" ? "[PASS] getFrontBeverage\n" : "[FAIL] getFrontBeverage\n");

    slot.popFrontBeverage();
    std::cout << (slot.getCurrentCount() == 1 ? "[PASS] popFrontBeverage\n" : "[FAIL] popFrontBeverage\n");

    slot.popFrontBeverage();
    std::cout << (slot.isEmpty() ? "[PASS] isEmpty\n" : "[FAIL] isEmpty\n");
}

void test_dispenser_bin() {
    std::cout << "Testing DispenserBin...\n";

    DispenserBin bin;
    std::cout << (!bin.isOccupied() ? "[PASS] Empty bin\n" : "[FAIL] Should be empty\n");

    bin.placeBeverage(Beverage("Tea"));
    std::cout << (bin.isOccupied() ? "[PASS] Bin occupied\n" : "[FAIL] Should be occupied\n");

    bin.collectBeverage();  // Collect the drink
    std::cout << (!bin.isOccupied() ? "[PASS] Bin cleared\n" : "[FAIL] Bin should be empty again\n");
}

void test_dispenser_states() {
    std::cout << "Testing DispenserContainer state transitions...\n";

    EventManager manager;
    DispenserContainer dispenser(&manager);

    dispenser.enterProcessingMode();
    std::cout << (dispenser.getState() == "Processing" ? "[PASS] Processing mode\n" : "[FAIL] Processing mode\n");

    dispenser.enterMaintenanceMode();
    std::cout << (dispenser.getState() == "Maintenance" ? "[PASS] Maintenance mode\n" : "[FAIL] Maintenance mode\n");

    dispenser.enterIdleMode();
    std::cout << (dispenser.getState() == "Idle" ? "[PASS] Idle mode\n" : "[FAIL] Idle mode\n");
}

// === FULL TRANSACTION FLOW ===

void preloadTestSlots(std::vector<Slot>& storage) {
    Slot s1(1, 1.00, 2);
    Slot s2(2, 1.25, 1);
    Slot s3(3, 0.75, 1);

    s1.fillBeverage(Beverage("Coke"));
    s1.fillBeverage(Beverage("Coke"));
    s2.fillBeverage(Beverage("Sprite")); // s3 stays empty

    storage.push_back(s1);
    storage.push_back(s2);
    storage.push_back(s3);
}

void simulate_dispense(DispenserContainer& dispenser, EventManager& manager, double amount) {
    EventData data;
    data.inserted_amount = amount;
    manager.notify(EventType::FundsAvailable, data);
}

void full_functionality_test() {
    std::cout << "\n--- FULL FUNCTIONALITY TEST ---\n";

    EventManager manager;
    DispenserContainer dispenser(&manager);
    preloadTestSlots(dispenser.getStorage());

    dispenser.displayMenu();

    std::cout << "\n[TEST] Insert $1.00 (select Coke)...\n";
    simulate_dispense(dispenser, manager, 1.00);

    std::cout << "\n[TEST] Insert $1.25 while bin is full (should be blocked)...\n";
    simulate_dispense(dispenser, manager, 1.25); // will print bin full

    std::cout << "\n[TEST] Collect item from bin...\n";
    dispenser.collectItem();

    std::cout << "\n[TEST] Insert $1.25 again (select Sprite)...\n";
    simulate_dispense(dispenser, manager, 1.25);
    dispenser.collectItem();

    std::cout << "\n[TEST] Insert $0.75 (attempt to select empty slot)...\n";
    simulate_dispense(dispenser, manager, 0.75);
    dispenser.collectItem();

    std::cout << "\n--- Final Slot Inventory ---\n";
    dispenser.displayMenu();
}

// === MAIN ===
/*
int main() {
    std::cout << "=== DISPENSER COMPONENT BASIC TESTS ===\n";

    test_beverage_class();
    test_slot_class();
    test_dispenser_bin();
    test_dispenser_states();
    full_functionality_test();

    std::cout << "=== ALL TESTS COMPLETED ===\n";
    return 0;
}
*/

//TEST RESULTS

/*
PS C:\Users\welld\source\repos\VsCodeVMTest\VendingMachine> g++ -Iheader source/dispenser/beverage.cpp source/dispenser/slot.cpp source/dispenser/dispenser_bin.cpp source/dispenser/dispenser_container.cpp source/dispenser/dispenser_container_io.cpp source/event/event_manager.cpp source/dispenser/dispenser_test.cpp -std=c++20 -o dispenser_test.exe       
>> 
PS C:\Users\welld\source\repos\VsCodeVMTest\VendingMachine> .\dispenser_test.exe
>>                                                                            
=== DISPENSER COMPONENT BASIC TESTS ===                                       
Testing Beverage class...
[PASS] Default name
[PASS] Parameter name
[PASS] setName
Testing Slot class...
[PASS] Slot full correctly blocked
[PASS] getFrontBeverage
[PASS] popFrontBeverage
[PASS] isEmpty
Testing DispenserBin...
[PASS] Empty bin
Tea is now in the bin. Please collect it.
[PASS] Bin occupied
You collected: Tea
[PASS] Bin cleared
Testing DispenserContainer state transitions...
[PASS] Processing mode
[PASS] Maintenance mode
[PASS] Idle mode

--- FULL FUNCTIONALITY TEST ---
==== BEVERAGE MENU ====
[1] Coke $1
[2] Sprite $1.25
[X] No Beverage $0.75

[TEST] Insert $1.00 (select Coke)...
==== BEVERAGE MENU ====
[1] Coke $1
[2] Sprite $1.25
[X] No Beverage $0.75
Please enter your selection number: 1
You selected: Coke
You selected: Coke - Price: $1
Dispensing Coke...
Coke is now in the bin. Please collect it.
Dispensing: Coke

[TEST] Insert $1.25 while bin is full (should be blocked)...
==== BEVERAGE MENU ====
[1] Coke $1
[2] Sprite $1.25
[X] No Beverage $0.75
Please enter your selection number: 2
You selected: Sprite
You selected: Sprite - Price: $1.25
Please collect your previous beverage first!

[TEST] Collect item from bin...
You collected: Coke

[TEST] Insert $1.25 again (select Sprite)...
==== BEVERAGE MENU ====
[1] Coke $1
[2] Sprite $1.25
[X] No Beverage $0.75
Please enter your selection number: 2
You selected: Sprite
You selected: Sprite - Price: $1.25
Dispensing Sprite...
Sprite is now in the bin. Please collect it.
Dispensing: Sprite
You collected: Sprite

[TEST] Insert $0.75 (attempt to select empty slot)...
==== BEVERAGE MENU ====
[1] Coke $1
[X] No Beverage $1.25
[X] No Beverage $0.75
Please enter your selection number: x
Invalid input. Please enter a number.
Please enter your selection number: 2
Selected slot is empty! Please choose another.
Please enter your selection number: 1
You selected: Coke
You selected: Coke - Price: $1
Dispensing Coke...
Coke is now in the bin. Please collect it.
Dispensing: Coke
You collected: Coke

--- Final Slot Inventory ---
==== BEVERAGE MENU ====
[X] No Beverage $1
[X] No Beverage $1.25
[X] No Beverage $0.75
=== ALL TESTS COMPLETED ===

*/
