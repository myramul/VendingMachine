// COIN.H

#ifndef COIN_H
#define COIN_H

#include <unordered_map>
#include <string>
#include "coin_io.h"

using std::unordered_map;

class Coin{
    public:
        Coin(std::string name);
        bool isValid(std::string name);
        double getNumericalValue();
        void displayCoin() const;
    private:
        const static std::unordered_map<std::string, double> coin_values;
        double numerical_value;
        std::string name;
        CoinIO io;
}; 

const std::unordered_map<std::string, double> Coin::coin_values = {
        {"NICKEL", 0.05}, 
        {"DIME", 0.10}, 
        {"QUARTER", 0.25}
};

#endif