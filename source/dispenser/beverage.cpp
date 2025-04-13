// Class implemantion


#include "beverage.h"


// Default constructor 

Beverage::Beverage() {
	// Initialize the beverage name to an empty string
	beverageName = "";
}

Beverage::Beverage(const string name) {
	// Initialize the beverage name with the provided name
	beverageName = name;
}

void Beverage::setName(string name) {
	// Set the beverage name to the provided name
	beverageName = name;
}

string Beverage::getName() const {
	// Return the beverage name
	return beverageName;
}
