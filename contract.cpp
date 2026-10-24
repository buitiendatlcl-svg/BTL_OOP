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
	term = 0;
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

void contract::setTerm(int term){
	this->term = term;
}
int contract::getTerm(){
	return term;
}

void contract::inputFromKeyboard(){
}

void contract::showToConsole(){
	cout << left << setw(20) << getId()
		 << "| " << setw(15) << customerId
		 << "| " << setw(15) << packageId
		 << "| " << setw(15) << areaId 
		 << "| " << setw(15) << signDate
		 << "| " << setw(10) << (to_string(term) + " thang") << endl;
}

string contract::toFileString(){
	return getId() + "|" + getCustomerId() + "|" + getPackageId() + "|" + getAreaId() + "|" +signDate + "|" + to_string(term);
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
	
	string termStr;
	getline(ss, termStr, '|');
	try {
		term = stoi(termStr);
	} catch(...) {
		term = 0;
	}
}


