// Nguyen Manh Khanh - B24DCVT192
#include "Customer.h"
#include <iostream> 
#include <iomanip>
#include <sstream> 
#include <cctype>
using namespace std;

string Customer::chuanHoa(string s){
	stringstream ss(s);
	string word, res = "";
	while(ss >> word){
		res += toupper(static_cast<unsigned char>(word[0]));
		for(size_t i = 1; i < word.size(); i++){
			res += tolower(static_cast<unsigned char>(word[i]));
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
    if (s.empty()) return false;
    bool hasLetter = false;
    for (char c : s) {
        if (isalpha(static_cast<unsigned char>(c))) {
            hasLetter = true; // Kiem tra it nhat phai co 1 chu cai
        } 
        else if (!isspace(static_cast<unsigned char>(c))) { // Neu khong phai chu cai va dau cach -> khong hop le
            return false; 
        }
    }
    return hasLetter;
}

bool Customer::isValidPhoneNumber(string s){
	if (s.length() != 10 || s[0] != '0') return false;
	for (char c : s) {
		if (!isdigit(static_cast<unsigned char>(c))) return false;
	}
	return true;
}

bool Customer::isValidNationalId(string s){
	if (s.length() != 12 || s[0] != '0') return false;
	for (char c : s) {
		if (!isdigit(static_cast<unsigned char>(c))) return false;
	}
	return true;
}

void Customer::inputFromKeyboard(){
	string temp;
	while(true){
		cout << "Nhap Ho va Ten (Nhap '0' de quay lai): ";
		getline(cin, temp);
		if(temp == "0"){
			name = "";
			nationalId = "";
			phoneNumber = "";
			return;
		}
		if(isValidName(temp)){
			setName(temp);
			break;
		}
		cout << "\n[THONG BAO]: Ho va ten khong hop le! Vui long chi nhap chu cai va khoang trang!" << endl;
	}
		
	while(true){
		cout << "Nhap so CCCD (gom 12 chu so va bat dau tu '0') (Nhap '0' de quay lai): ";
		getline(cin, temp);
		if(temp == "0"){
			name = "";
			nationalId = "";
			phoneNumber = "";
			return;
		}
		if(isValidNationalId(temp)){
			setNationalId(temp);
			break;
		} 
		else{
			cout << "\n[THONG BAO]: So CCCD khong hop le (phai du 12 chu so va bat dau bang '0')! Vui long nhap lai!" << endl;
			continue;
		}
	}
	
	while(true){
		cout << "Nhap so dien thoai (gom 10 chu so va bat dau tu '0') (Nhap '0' de quay lai): ";
		getline(cin, temp);
		if(temp == "0"){
			name = "";
			nationalId = "";
			phoneNumber = "";
			return;
		}
		if(isValidPhoneNumber(temp)){
			setPhoneNumber(temp);
			break;
		}
		else{
			cout << "\n[THONG BAO]: So dien thoai khong hop le (phai du 10 so va bat dau bang '0')! Vui long nhap lai!" << endl;
			continue;
		}
	}
}

void Customer::showToConsole() {
	cout << left << setw(10) << id 
	     << "| " << setw(25) << name 
	     << "| " << setw(16) << nationalId 
	     << "| " << setw(15) << phoneNumber 
	     << "| " << address << endl;
}

string Customer::toFileString() {
	return id + "|" + name + "|" + nationalId + "|" + phoneNumber + "|" + address;
}

void Customer::fromFileString(string& line){
	stringstream ss(line);
	getline(ss, id, '|');
	getline(ss, name, '|');
	getline(ss, nationalId, '|');
	getline(ss, phoneNumber, '|');
	getline(ss, address, '|');
}
