//Bui Tien Dat - B24DCVT062
#pragma once
#include "Entity.h"
#include <string>
#include <vector>
using namespace std;

class internet : public entity{
private:
	string packageName, customerType;
	int speed;
	double price;
public:
	
	internet();
	
	void setPackageName(string packageName);
	string getPackageName();
	
	void setSpeed(int speed);
	int getSpeed();
	
	void setCustomerType(string customerType);
	string getCustomerType();
	
	void setPrice(double price);
	double getPrice();
	
	void inputFromKeyboard();
	void inputFromKeyboard(vector<internet> list); // lay du lieu tu ban phim
	
	void showToConsole();
	
	string toFileString();
	
	void fromFileString(string &line);	
};
