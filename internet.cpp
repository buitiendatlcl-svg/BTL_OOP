#include "internet.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

internet::internet(){
	packageName = "";
	speed = 0;
	customerType = "";
	price = 0;
}

void internet::setPackageName(string packageName){
	this->packageName = packageName; 
}
string internet::getPackageName(){
	return packageName;
}

void internet::setSpeed(int speed){
	this->speed = speed;
}
int internet::getSpeed(){
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
	
	cout << "Nhap ten goi moi: ";
	getline(cin, temp);
	setPackageName(temp);
	
	int speed;
	while(true){
		cout << "Nhap toc do: ";
		getline(cin, temp);
		try{
			speed = stoi(temp);
			if(speed < 0){
				cout << "[Loi]Vui long chi nhap lai!" << endl; 
			}
			else
				break;
		}
		catch(...){
			cout << "[Loi]Vui long nhap lai!" << endl;
		}
	}
	setSpeed(speed);
	
	cout << "Nhap tep khach hang: ";
	getline(cin, temp);
	setCustomerType(temp);
	
	double price;
	while(true){
		cout << "Nhap gia dich vu(VND): ";
		getline(cin, temp);
		try{
			price = stod(temp);
			if(price < 0){
				cout << "[Loi]Vui long chi nhap lai!" << endl; 
			}
			else
				break;
		}
		catch(...){
			cout << "[Loi]Vui long nhap lai!" << endl;
		}
	}
	setPrice(price);

}

void internet::showToConsole(){
	cout << getId() << "|" << packageName << "|" << speed << "|" << customerType << "|" << price << endl;
}

string internet::toFileString(){
	string strPrice = to_string(price);
	string strSpeed = to_string(speed);
	return getId() + "|" + packageName + "|" + strSpeed + "|" + customerType + "|" + strPrice;
}

void internet::fromFileString(string &s){
	stringstream ss(s);
	string tmp;
	getline(ss, tmp, '|');
	setId(tmp);
	
	getline(ss, packageName, '|');
	
	getline(ss, tmp, '|');
	speed = stoi(tmp);
	
	getline(ss, customerType, '|');
	
	getline(ss, tmp, '|');
	price = stod(tmp);
}


