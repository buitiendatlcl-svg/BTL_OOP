#include "customer.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

customer::customer(){
	fullName = "";
	dateOfBirth = "";
	address = "";
	phoneNumber = "";
	setId("");
}

void customer::setFullName(string fullName){
	this->fullName = fullName;
}
string customer::getFullName(){
	return fullName;
}

void customer::setDateOfBirth(string dateOfBirth){
	this->dateOfBirth = dateOfBirth;
}
string customer::getDateOfBirth(){
	return dateOfBirth;
}

void customer::setAddress(string address){
	this->address = address;
}
string customer::getAddress(){
	return address;
}

void customer::setPhoneNumber(string phoneNumber){
	this->phoneNumber = phoneNumber;
}
string customer::getPhoneNumber(){
	return phoneNumber;
}

void customer::inputFromKeyboard(){
	string temp;
	cout << "Nhap ma dinh danh: ";
	getline(cin, temp);
	setId(temp);
	
	cout << "Nhap ten: ";
	getline(cin, temp);
	setFullName(temp);
	
	cout << "Nhap ngay sinh: ";
	getline(cin, temp);
	setDateOfBirth(temp);
	
	cout << "Nhap dia chi: ";
	getline(cin, temp);
	setAddress(temp);
	
	cout << "Nhap sdt: ";
	getline(cin, temp);
	setPhoneNumber(temp);
}

void customer::showToConsole(){
	cout << id << "|" << fullName << "|" << dateOfBirth << "|" << address << "|" << phoneNumber << endl;
}

string customer::toFileString(){
	return id + "|" + fullName + "|" + dateOfBirth + "|" + address + "|" + phoneNumber;
}

void customer::fromFileString(string &s){
	stringstream ss(s);
	string tmp;
	getline(ss, id, '|');
	
	getline(ss, fullName, '|');
	
	getline(ss, dateOfBirth, '|');
	
	getline(ss, phoneNumber, '|');
}




