// coin io cpp

#include "money/coin_io.h"
#include <iomanip>

void CoinIO::displayCoin(const std::string& name, double value) const {
    std::cout << name << ": $" << std::fixed << std::setprecision(2) << value << std::endl;
}