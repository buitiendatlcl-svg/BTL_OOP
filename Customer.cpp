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

bool Customer::isValidName(string s){
	for(auto& c : s){
		if(isspace(c))
			continue;
		if(!isalpha(c)) return false;
	}
	return true;
}

bool Customer::isValidPhoneNumber(string s){
	for(auto& c : s){
		if(!isdigit(c)) return false;
	}
	if(s[0] == '0' && s.size() == 10)
		return true;
	else
		return false;
}

bool Customer::isValidNationalId(string s){
	if(s[0] != '0') return false;
	for(auto& c : s){
		if(!isdigit(c)) return false;
	}
	return true;
}

void Customer::inputFromKeyboard(){
	while(true){
		cout << "Nhap Ho va Ten (Nhap '0' de quay lai): ";
		getline(cin, name);
		if(name == "0"){
			name = "";
			return;
		}
		if(isValidName(name)){
			setName(name);
			break;
		}
		else{
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}
	}
		
	
	while(true){
		cout << "Nhap so CCCD (Nhap '0' de quay lai): ";
		getline(cin, nationalId);
		if(nationalId == "0"){
			nationalId = "";
			return;
		}
		if(isValidNationalId(nationalId)){
			setNationalId(nationalId);
			break;
		} 
		else{
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}
	}
	
	while(true){
		cout << "Nhap so dien thoai (Nhap '0' de quay lai):";
		getline(cin, phoneNumber);
		if(phoneNumber== "0"){
			phoneNumber = "";
			return;
		}
		if(isValidPhoneNumber(phoneNumber)){
			setPhoneNumber(phoneNumber);
			break;
		}
		else{
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}
	}
	
	cout << "Nhap dia chi nha (Nhap '0' de quay lai): ";
	getline(cin, address);
	setAddress(address);
	if(address== "0"){
		address = "";
		return;
	}
}

void Customer::showToConsole() {
	cout << left << setw(10) << id << setw(25) << name << setw(20) << nationalId << setw(20) << phoneNumber << setw(20) << address << endl;
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
