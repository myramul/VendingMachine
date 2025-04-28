#include "vending_machine/vending_machine.h"
#include "vending_machine/vending_machine_io.h"
#include <iostream>

int main() {
    // Create instance of VendingMachineIO
    VendingMachineIO io;

    // Create an instance of VendingMachine
    VendingMachine vendingMachine(&io);

    std::cout << "Testing displayWelcomeMessage:\n";
    io.displayWelcomeMessage();

    std::cout << "\nTesting displayMaintenanceMenu:\n";
    io.displayMaintenanceMenu();

    std::cout << "\nTesting handleMaintenanceMenuSelection:\n";
    io.handleMaintenanceMenuSelection();

    std::cout << "\nTesting setState to Processing:\n";
    vendingMachine.setState("Processing"); // state is not a string anymore

    std::cout << "\nTesting enterIdleMode:\n";
    vendingMachine.enterIdleMode();

    std::cout << "\nTesting enterMaintenanceMode:\n";
    vendingMachine.enterMaintenanceMode();

    std::cout << "\nTesting enterProcessingMode:\n";
    vendingMachine.enterProcessingMode();

    std::cout << "\nTesting initializeMachine:\n";
    vendingMachine.initializeMachine();

    std::cout << "\nTesting unlockMachine with wrong password:\n";
    vendingMachine.unlockMachine("wrong123");

    std::cout << "\nTesting unlockMachine with correct password:\n";
    vendingMachine.unlockMachine("admin123");

    std::cout << "\nTesting authenticateMaintenancePasscode with wrong passcode:\n";
    bool auth1 = vendingMachine.authenticateMaintenancePasscode("1234");
    std::cout << "Authentication result: " << (auth1 ? "Success" : "Failure") << std::endl;

    std::cout << "\nTesting authenticateMaintenancePasscode with correct passcode:\n";
    bool auth2 = vendingMachine.authenticateMaintenancePasscode("admin123");
    std::cout << "Authentication result: " << (auth2 ? "Success" : "Failure") << std::endl;

    std::cout << "\nTesting onTransactionComplete:\n";
    vendingMachine.onTransactionComplete();

    std::cout << "\nTesting lockMachine:\n";
    vendingMachine.lockMachine();

    std::cout << "\nAll tests executed.\n";
    return 0;
}
