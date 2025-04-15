// coin.cpp

#include "money/coin.h"
#include <algorithm>  
#include <cctype>   
#include <iostream>  

const std::unordered_map<std::string, double> Coin::coin_values = {
    {"QUARTER", 0.25},
    {"DIME", 0.10}, 
    {"NICKEL", 0.05}
};

Coin::Coin(std::string name) : name(name) {
    std::transform(this->name.begin(), this->name.end(), this->name.begin(), ::toupper);
    
    if (isValidCoin(this->name)) {
        numerical_value = coin_values.at(this->name);
    } else {
        numerical_value = 0.0;
    }
}

bool Coin::isValidCoin(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    return coin_values.find(name) != coin_values.end();
}

double Coin::getNumericalValue() {
    return numerical_value;
}

std::string Coin::getName() {
    return name;
}