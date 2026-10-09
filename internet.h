#pragma once
#include "entity.h"
#include <string>

using namespace std;

class internet : public entity{
private:
	string packageName, speed, customerType;
	double price;
public:
	
	internet();
	
	void setPackageName(string packageName);
	string getPackageName();
	
	void setSpeed(string speed);
	string getSpeed();
	
	void setCustomerType(string customerType);
	string getCustomerType();
	
	void setPrice(double price);
	double getPrice();
	
	void inputFromKeyboard();
	
	void showToConsole();
	
	string toFileString();
	
	void fromFileString(string &line);	
};
