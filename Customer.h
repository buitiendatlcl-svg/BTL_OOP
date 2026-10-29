// Nguyen Manh Khanh - B24DCVT194
#pragma once 
#include <string>
#include <iostream>
#include "Entity.h"
using namespace std;

class Customer : public entity{
private : 
	string name;
	string nationalId;
	string phoneNumber;
	string address;
	
	
	string chuanHoa(string s);
public : 
	Customer();
	
	void setName(string Name);
	string getName();
	
	void setNationalId(string NationalId);
	string getNationalId();
	
	void setPhoneNumber(string PhoneNumber);
	string getPhoneNumber();
	
	void setAddress(string Address);
	string getAddress();
	
	
	bool isValidName(string s);
	bool isValidPhoneNumber(string s);
	bool isValidNationalId(string s);
	
	void inputFromKeyboard() override;
	void showToConsole() override;
	string toFileString() override;
	void fromFileString(string& line) override;							
};


