#ifndef BEVERAGE_H
#define BEVERAGE_H

#include <string>

class Beverage {
private:
    std::string beverageName;

public:
    Beverage();  // default constructor
    Beverage(const std::string& name);  // constructor with name

    void setName(const std::string& name);
    std::string getName() const;
};

#endif // BEVERAGE_H

