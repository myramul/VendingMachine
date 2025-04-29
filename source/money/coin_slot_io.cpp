// coin slot io cpp

#include "money/coin_slot_io.h"
#include "money/coin_slot.h"
#include "money/coin.h"
#include <iomanip>

CoinSlotIO::CoinSlotIO(CoinSlot* owner) : coin_slot(owner) {}
void CoinSlotIO::insertCoins(bool exactChangeMode, CoinReturn* coinReturn) {
    bool coin_return = false;
    if (exactChangeMode) {
        std::cout << "!! NOTICE: EXACT CHANGE ONLY. \nThe machine will not dispense any change if you overpay. !!" << std::endl;
    }
    std::string input;
    std::cout << "Insert coins (type coin name like 'Quarter', 'Dime', 'Nickel') or 'X' FOR COIN RETURN:" << std::endl;

    do {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "X" || input == "x") {
            coin_return = true;
            coinReturn->returnCoins(coin_slot->totalInsertedMoney);
            break;
        }

        Coin coin(input);  // Create coin based on name

        if (coin.isValidCoin(input)) {
            coin_slot->addCoin(coin);
            std::cout << "Accepted: " << input << std::endl;
        } else {
            std::cout << "Coin not accepted. Returning " << input << "." << std::endl;
        }

        std::cout << "Current inserted: $" << std::fixed << std::setprecision(2) << coin_slot->getTotalInsertedValue() << std::endl;
        if (coin_slot->getTotalInsertedValue() == coin_slot->getMinimumValue()) {
            break;
        }
    } while (coin_slot->getTotalInsertedValue() < coin_slot->getMinimumValue());
    if (!coin_return){
        coin_slot->notifyFundsAvailable();
    }
}

void CoinSlotIO::displayTotalinsertedCoins(double totalInsertedValue){
    std::cout << "Total Inserted: " << totalInsertedValue << std::endl;
}