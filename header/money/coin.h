// COIN.H

#ifndef COIN_H
#define COIN_H

#include <unordered_map>
#include <string>
#include "money/coin_io.h"

using std::unordered_map;

class Coin{
    public:
        Coin(std::string name);
        bool isValidCoin(std::string name);
        double getNumericalValue();
        std::string getName();
        const static std::unordered_map<std::string, double> coin_values;
    private:
        double numerical_value;
        std::string name;
        CoinIO io;
}; 

#endif