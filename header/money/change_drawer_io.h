#ifndef CHANGE_DRAWER_IO_H
#define CHANGE_DRAWER_IO_H

#include <iostream>

class ChangeDrawerIO {
    public:
        void inputChangeCoins();
        void displayChangeLevels(std::unordered_map<std::string, double> levels) const;
};

#endif