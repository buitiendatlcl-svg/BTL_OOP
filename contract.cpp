#include "contract.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

contract::contract(){
	customerId = "";
	packageId = "";
	areaId = "";
	signDate = "";
	status = false;
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
	this->signDate = signDate;
}
string contract::getSignDate(){
	return signDate;
}

void contract::setStatus(bool status){
	this->status = status;
}
bool contract::getStatus(){
	return status;
}

void contract::inputFromKeyboard(){
	string tmp;
	cout << "Nhap ngay ky hop dong(dd/mm/yy): ";
	getline(cin, tmp);
	setSignDate(tmp);
	
	int option;
	cout << "Nhap trang thai (1 - Hoat dong, 0 - Khong hoat dong): ";
	cin >> option;
	cin.ignore();
	setStatus(option);
	
}

void contract::showToConsole(){
	cout << getId() << "|" << getCustomerId() << "|" << getPackageId() << "|" << getAreaId() << "|" << signDate	<< "|" << status<<endl;
}

string contract::toFileString(){
	if(status){
		return getId() + "|" + getCustomerId() + "|" + getPackageId() + "|" + getAreaId() + "|" + signDate + "|" + "Hoat dong";
	}
	else
		return getId() + "|" + getCustomerId() + "|" + getPackageId() + "|" + getAreaId() + "|" +signDate + "|" + "Khong hoat dong";
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
	
	string statusStr;
	getline(ss, statusStr, '|');
	if (statusStr == "Hoat dong"){
	    setStatus(true);
	} 
	else{
	    setStatus(false);
	}
}





