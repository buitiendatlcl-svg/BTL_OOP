#include "internet.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

internet::internet(){
	packageName = "";
	speed = "";
	customerType = "";
	price = 0;
}

void internet::setPackageName(string packageName){
	this->packageName = packageName; 
}
string internet::getPackageName(){
	return packageName;
}

void internet::setSpeed(string speed){
	this->speed = speed;
}
string internet::getSpeed(){
	return speed;
}

void internet::setCustomerType(string customerType){
	this->customerType = customerType;
}
string internet::getCustomerType(){
	return customerType;
} 

void internet::setPrice(double price){
	this->price = price;
}
double internet::getPrice(){
	return price;
}

void internet::inputFromKeyboard(){
	string temp;
	
//	cout << "Nhap ma goi moi: ";
//	getline(cin, temp);
//	setId(temp);
	
	cout << "Nhap ten goi moi: ";
	getline(cin, temp);
	setPackageName(temp);
	
	cout << "Nhap toc do: ";
	getline(cin, temp);
	setSpeed(temp);
	
	cout << "Nhap tep khach hang: ";
	getline(cin, temp);
	setCustomerType(temp);
	
	cout << "Nhap gia dich vu(VND): ";
	double price;
	cin >> price;
	setPrice(price);
	cin.ignore();

}

void internet::showToConsole(){
	cout << getId() << "|" << packageName << "|" << speed << "|" << customerType << "|" << price << endl;
}

string internet::toFileString(){
	string strPrice = to_string(price);
	return getId() + "|" + packageName + "|" + speed + "|" + customerType + "|" + strPrice;
}

void internet::fromFileString(string &s){
	stringstream ss(s);
	string tmp;
	getline(ss, tmp, '|');
	setId(tmp);
	
	getline(ss, packageName, '|');
	
	getline(ss, speed, '|');
	
	getline(ss, customerType, '|');
	
	getline(ss, tmp, '|');
	price = stod(tmp);
}


