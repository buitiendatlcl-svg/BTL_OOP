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
	
	cout << "Nhap ten goi moi (Nhap 0 de quay lai): ";
	getline(cin, temp);
	if(temp == "0"){
		setId("");
		return;
	}
	setPackageName(temp);
	
	int speed;
	while(true){
		cout << "Nhap toc do (Nhap 0 de quay lai): ";
		getline(cin, temp);
		if(temp == "0"){
			setId("");
			return;
		}
		try{
			size_t pos;
			speed = stoi(temp, &pos);
			if(pos != temp.size() || speed <= 0){
				cout << "[Loi]Vui long nhap lai!" << endl;
			}
			else
				break;
		}
		catch(...){
			cout << "[Loi]Vui long nhap lai!" << endl;
		}
	}
	setSpeed(speed);
	
	int choice = -1;
	do{
		cout << "Cac tep khach hang:" << endl;
		cout << "1. Ca nhan" << endl;
		cout << "2. Gia dinh" << endl;
		cout << "3. Doanh nghiep" << endl;
		cout << "0. Quay lai" << endl;
		cout << "Nhap lua chon cua ban: ";
		string choiceStr;
		getline(cin, choiceStr);
		if(choiceStr == "0"){
			setId("");
			return;
		}
		try{
			size_t pos;
			choice = stoi(choiceStr, &pos);
			if(pos != choiceStr.size())
				choice = -1;
		}catch(...){
			choice = -1;
		}
		switch(choice){
			case 1: {
				setCustomerType("Ca nhan");
				break;
			}
			case 2: {
				setCustomerType("Gia dinh");
				break;
			}
			case 3: {
				setCustomerType("Doanh nghiep");
				break;
			}
			default:{
				cout << "[LOI] Vui long nhap lai!" << endl;
				break;
			}
		}
	}while(choice < 1 || choice > 3);

	double price;
	while(true){
		cout << "Nhap gia dich vu(VND/Thang) (Nhap 0 de quay lai): ";
		getline(cin, temp);
		if(temp == "0"){
			setId("");
			return;
		}
		try{
			size_t pos;
			price = stod(temp, &pos);
			if(price < 0 || pos != temp.size()){
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
	cout << left << setw(8)  << getId() 
	     << "| " << setw(20) << packageName 
	     << "| " << setw(15) << speed 
	     << "| " << setw(20) << customerType 
	     << "| " << (long long)price << endl;
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


