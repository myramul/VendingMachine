#ifndef BEVERAGE_H
#define BEVERAGE_H
#include <string>

namespace using std;


class Beverage {

private: string beverageName;

public :
	Beverage(); //default 
	Beverage(const string name); // should we pass string as a reference???? or leave it like tbis??????
	void setName(string name);// should we pass string as a reference???? or leave it like tbis??????
	string getName() const;

};

#endif // BEVERAGE_H
