// coin slot io cpp

#include "money/coin_slot_io.h"
#include "money/coin_slot.h"
#include "money/coin.h"

CoinSlotIO::CoinSlotIO(CoinSlot* owner) : coin_slot(owner) {}
void CoinSlotIO::insertCoins() {
    std::string input;
    std::cout << "Insert coins (type coin name like 'Quarter', 'Dime', 'Nickel'):" << std::endl;

    while (coin_slot->getTotalInsertedValue() < coin_slot->getMinimumValue()) {
        std::cout << "> ";
        std::getline(std::cin, input);

        Coin coin(input);  // Create coin based on name

        if (coin.isValidCoin(input)) {
            coin_slot->addCoin(coin);
            std::cout << "Accepted: " << input << std::endl;
        } else {
            std::cout << "Coin not accepted. Returning " << input << "." << std::endl;
        }

        std::cout << "Current inserted: $" << coin_slot->getTotalInsertedValue() << std::endl;
    }

    coin_slot->notifyFundsAvailable();
}

void CoinSlotIO::displayTotalinsertedCoins(double totalInsertedValue){
    std::cout << "Total Inserted: " << totalInsertedValue << std::endl;
}