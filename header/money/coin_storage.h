// COIN_STORAGE.H

#ifndef COIN_STORAGE_H
#define COIN_STORAGE_H

#include <unordered_map>
#include <string>

class CoinStorage {
    public:
        CoinStorage();
        virtual void add_coin(std::string name, int quantity);
        virtual void remove_coins(std::string name, int quantity);
        virtual int get_coin_count(std::string name);
    private:
        std::unordered_map<std::string, int> coin_storage;
        double calculateTotalValue();
        double total_value;
};

#endif