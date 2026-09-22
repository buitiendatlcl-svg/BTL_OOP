#pragma once
#include "entity.h"
#include <string>

using namespace std;

class customer : public entity {
private:
	string fullName, dateOfBirth, address, phoneNumber;
public:
	customer();
	
	//cac ham setter va getter phai co cho moi thuoc tinh
	void setFullName(string fullName);
	string getFullName();
	
	void setDateOfBirth(string dateOfBirth);
	string getDateOfBirth();
	
	void setAddress(string address);
	string getAddress();
	
	void setPhoneNumber(string phoneNumber);
	string getPhoneNumber();
	
	//cac ham phuc vu thao tac nhap, luu file -> cac ham virtual trong entity.h
	void inputFromKeyboard();
	
	void showToConsole();
	
	string toFileString();
	
	void fromFileString(string &line);

};
