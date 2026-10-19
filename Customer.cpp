#include "Customer.h"
#include <iostream> 
#include <iomanip>
#include <sstream> 
#include <ctype.h>

using namespace std;

string Customer::chuanHoa(string s){
	stringstream ss(s);
	string word, res = "";
	while(ss >> word){
		res += toupper(word[0]);
		for(size_t i = 1; i < word.size(); i++){
			res += tolower(word[i]);
		}	
		res += " ";	
	}
	if(!res.empty()){
		res.pop_back(); // Xoa dau cach thua o cuoi
	}
	return res;
}

Customer::Customer(){
	id = "";
	name = "";
	nationalId = "";
	phoneNumber = "";
	address = "";
}

void Customer::setName(string name){
	this->name = chuanHoa(name);
}
string Customer::getName() {
	return name;
}

void Customer::setNationalId(string nationalId){
	this->nationalId = nationalId;
}
string Customer::getNationalId() {
	return nationalId;
}

void Customer::setPhoneNumber(string phoneNumber){
	this->phoneNumber = phoneNumber;
}
string Customer::getPhoneNumber() {
	return phoneNumber;
}

void Customer::setAddress(string address){
	this->address = chuanHoa(address);
}
string Customer::getAddress() {
	return address;
}

void Customer::inputFromKeyboard(){
	cout << "Nhap ma khach hang: ";
	getline(cin, id);
	
	cout << "Nhap Ho va Ten: ";
	getline(cin, name);
	setName(name);
	
	cout << "Nhap so CCCD: ";
	getline(cin, nationalId);
	
	cout << "Nhap so dien thoai: ";
	getline(cin, phoneNumber);
	
	cout << "Nhap dia chi nha: ";
	getline(cin, address);
	setAddress(address);
}

void Customer::showToConsole() {
	cout << left << setw(10) << id << setw(30) << name << setw(25) << nationalId << setw(25) << phoneNumber << setw(30) << address << endl;
}

string Customer::toFileString() {
	return id + "|" + name + "|" + nationalId + "|" + phoneNumber + "|" + address;
}

void Customer::fromFileString( string& line){
	stringstream ss(line);
	getline(ss, id, '|');
	getline(ss, name, '|');
	getline(ss, nationalId, '|');
	getline(ss, phoneNumber, '|');
	getline(ss, address, '|');
}


