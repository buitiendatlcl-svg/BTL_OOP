#include "contract.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

contract::contract(){
	customerId = "";
	packageId = "";
	areaId = "";
	signDate = "";
}

void contract::setCustomerId(string customerId){
	this->customerId = customerId;
}
string contract::getCustomerId(){
	return customerId;
}

void contract::setPackageId(string packageId){
	this->packageId = packageId;
}
string contract::getPackageId(){
	return packageId;
}

void contract::setAreaId(string areaId){
	this->areaId = areaId;
}
string contract::getAreaId(){
	return areaId;
}
void contract::setSignDate(string signDate){
	string temp = signDate;
	if(signDate[1] == '/') temp = "0" + signDate;
	if(temp[4] == '/') temp = temp.insert(3, 1, '0');
	signDate = temp;
	this->signDate = signDate;
}
string contract::getSignDate(){
	return signDate;
}

void contract::inputFromKeyboard(){
	string tmp;
	cout << "Nhap ngay ky hop dong(dd/mm/yy): ";
	getline(cin, tmp);
	setSignDate(tmp);
}

void contract::showToConsole(){
	cout << left << setw(20) << getId()
		 << "| " << setw(15) << customerId
		 << "| " << setw(15) << packageId
		 << "| " << setw(15) << areaId 
		 << "| " << setw(15) << signDate << endl;
}

string contract::toFileString(){
	return getId() + "|" + getCustomerId() + "|" + getPackageId() + "|" + getAreaId() + "|" +signDate + "|";
}

void contract::fromFileString(string &s){
	stringstream ss(s);
	string tmp;
	getline(ss, tmp, '|');
	setId(tmp);
	
	getline(ss, customerId, '|');
	
	getline(ss, packageId, '|');
	
	getline(ss, areaId, '|');
	
	getline(ss, signDate, '|');
}


