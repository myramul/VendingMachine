// Change drawer h file

#ifndef CHANGE_DRAWER_IO_H
#define CHANGE_DRAWER_IO_H

#include <iostream>
#include <unordered_map>

class ChangeDrawer;
class ChangeDrawerIO {
    public:
        void inputChangeCoins();
        void displayChangeLevels(std::unordered_map<std::string, int> levels) const;
        ChangeDrawerIO(ChangeDrawer* owner) : changeDrawer(owner) {}
    private:
        ChangeDrawer* changeDrawer;
};

#endif