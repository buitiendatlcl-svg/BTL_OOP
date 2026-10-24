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
	if(s[0] != '0' || s.size() != 10) return false;
	for(auto& c : s){
		if(!isdigit(c)) return false;
	}
	return true;
}

bool Customer::isValidNationalId(string s){
	if(s[0] != '0' || s[1] != '0') return false;
	for(auto& c : s){
		if(!isdigit(c)) return false;
	}
	return true;
}

void Customer::inputFromKeyboard(){
	string temp;
	while(true){
		cout << "Nhap Ho va Ten (Nhap '0' de quay lai): ";
		getline(cin, temp);
		if(temp == "0"){
			temp = "";
			return;
		}
		if(isValidName(temp)){
			setName(temp);
			break;
		}
		cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
	}
		
	
	while(true){
		cout << "Nhap so CCCD (CCCD hai chu so dau la '0') (Nhap '0' de quay lai) : ";
		getline(cin, temp);
		if(temp == "0"){
			temp = "";
			return;
		}
		if(isValidNationalId(temp)){
			setNationalId(temp);
			break;
		} 
		else{
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}
	}
	
	while(true){
		cout << "Nhap so dien thoai (SDT gom 10 so va bat dau tu 0) (Nhap '0' de quay lai):";
		getline(cin, temp);
		if(temp== "0"){
			temp = "";
			return;
		}
		if(isValidPhoneNumber(temp)){
			setPhoneNumber(temp);
			break;
		}
		else{
			cout << "\n[THONG BAO]: Vui long nhap lai !" << endl;
			continue;
		}
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


