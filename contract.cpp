//Bui Tien Dat - B24DCVT062
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
	status = 2;
	expiryDate = "none";
	feedback = "none";
}
bool contract::isValidDate(string date){ //check dinh dang dd/mm/yyyy
	if (date.size() != 10 || date[2] != '/' || date[5] != '/') return false;
	for (int i = 0; i < (int)date.size(); i++){
		if (i == 2 || i == 5) continue; // neu la dau "/" thi bo qua
		if (!isdigit(date[i])) return false;
	}
	
	int d = stoi(date.substr(0, 2)); 
	int m = stoi(date.substr(3, 2));
	int y = stoi(date.substr(6, 4));
	
	if ( d < 1 || m < 1 || m > 12 || y < 2000 || y > 2028 ) return false;
	
	int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29; // nam nhuan
    }
    return d <= daysInMonth[m]; // so sanh ngay nhap & ngay toi da cua thang do, neu dung tra ve true	
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
void contract::setStatus(int status){
	this->status = status;
}
int contract::getStatus(){
	return status;
}
void contract::setExpiryDate(string expiryDate){
	this->expiryDate = expiryDate;
}
string contract::getExpiryDate(){
	return expiryDate;
}
void contract::setFeedback(string feedback){
	bool isAllSpace = true;
	for(char c : feedback){
		if(!isspace(c)){
			isAllSpace = false;
			break;
		}
	}
	if(feedback.empty() || isAllSpace){
		this->feedback = "none";
	} else {
		this->feedback = feedback;
	}
}
string contract::getFeedback(){
	return feedback;
}


void contract::inputFromKeyboard(){
}
void contract::calculateExpiryDate(string installDate){
	if(installDate.empty() || installDate == "none" || term <= 0){
		this->expiryDate = "none";
		return;
	}
	
	
	string temp = installDate;
	if(temp.length() >= 2 && temp[1] == '/') temp = "0" + temp;
	if(temp.length() >= 5 && temp[4] == '/') temp.insert(3, 1, '0');
	
	try {
		int d = stoi(temp.substr(0, 2));
		int m = stoi(temp.substr(3, 2));
		int y = stoi(temp.substr(6, 4));
		
		int totalMonths = (m - 1) + this->term;
		y += totalMonths / 12;
		m = (totalMonths % 12) + 1;
		
	
		int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)){
			daysInMonth[2] = 29;
		}
		if(d > daysInMonth[m]){
			d = daysInMonth[m];
		}
		
		string dd = (d < 10 ? "0" : "") + to_string(d);
		string mm = (m < 10 ? "0" : "") + to_string(m);
		string yyyy = to_string(y);
		
		this->expiryDate = dd + "/" + mm + "/" + yyyy;
	} catch(...) {
		this->expiryDate = "none";
	}
}

void contract::showToConsole(){
	string statusText = (status == 1) ? "Hoat dong" : "Khong hoat dong";
	cout << left << setw(15) << getId()
		 << "| " << setw(15) << customerId
		 << "| " << setw(10) << packageId
		 << "| " << setw(12) << areaId 
		 << "| " << setw(12) << signDate
		 << "| " << setw(10) << (to_string(term) + " thang")
		 << "| " << setw(15) << expiryDate
		 << "| " << setw(16) << statusText
		 << "| " << feedback << endl;
}

string contract::toFileString(){
	return getId() + "|" + getCustomerId() + "|" + getPackageId() + "|" + getAreaId() + "|" +signDate + "|" + to_string(term) + "|" + to_string(status) + "|" + expiryDate + "|" + feedback;
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
	string statusStr;
	getline(ss, statusStr, '|');
	try {
		status = stoi(statusStr);
		if(status != 1 && status != 2) status = 2;
	} catch(...) {
		status = 2;
	}
	getline(ss, expiryDate, '|');
	if(expiryDate.empty()){
		expiryDate = "none";
	}
	getline(ss, feedback, '|');
	if(feedback.empty()){
		feedback = "none";
	}
}


