//Tran Hoang Hai - MSV: B24DCVT123
#include "employee.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

employee::employee (){
	fullName = "";
	dateOfBirth = "";
	phoneNumber = "";
	specialization = ""; //chuyen mon
	areaId = "";
	level = 1; //bac: 1,2,3
	salary = -1.0;
}

string employee :: standardizeName (string name) {
    string result = "";
    stringstream ss(name);
    string word;
    while (ss >> word){
    	word[0] = toupper(word[0]);
    	for(int i = 1; i < (int)word.size(); i++){
    		word[i] = tolower(word[i]);
    	}
    	if(!result.empty()){
    		result += " ";
		}
    	result += word;	
	}
    return result;
}
	
bool employee::isValidName(string name) { //check ten, chi duoc chua chu cai & khoang trang
    if (name.empty()) return false;
    bool hasLetter = false;
    for (char c : name) {
        if (isalpha(c)) {
            hasLetter = true; //kiem tra it nhat co 1 chu cai
        } else if (!isspace(c)) { //neu khong phai dau cach -> la ky tu dac biet khac -> tra ve false 
            return false; 
        }
    }
    return hasLetter;
}

bool employee::isValidDate(string date){ //check dinh dang dd/mm/yyyy
	if (date.size() != 10 || date[2] != '/' || date[5] != '/') return false;
	for (int i = 0; i < (int)date.size(); i++){
		if (i == 2 || i == 5) continue; // neu la dau "/" thi bo qua
		if (!isdigit(date[i])) return false;
	}
	
	int d = stoi(date.substr(0, 2)); 
	int m = stoi(date.substr(3, 2));
	int y = stoi(date.substr(6, 4));
	
	if ( d < 1 || m < 1 || m > 12 || y < 1900 || y > 2008 ) return false;
	
	int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29; // nam nhuan
    }
    return d <= daysInMonth[m]; // so sanh ngay nhap & ngay toi da cua thang do, neu dung tra ve true	
}

bool employee::isValidPhoneNumber(string phoneNumber) { //check dinh dang 10 so, 0xxx...
    if (phoneNumber.size() != 10 || phoneNumber[0] != '0') return false;
    for (char c : phoneNumber) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool employee::isValidSalary(string salaryStr) {
    if (salaryStr.empty()) return false;
    try {
        size_t pos;
        double sal = stod(salaryStr, &pos);
        if (pos == salaryStr.size() && sal >= 0) {
            return true;
        }
    } catch (...) {
        return false;
    }
    return false;        
}

void employee::setFullName(string fullName){
	this->fullName = standardizeName(fullName);
}
string employee::getFullName(){
	return fullName;
}

void employee :: setDateOfBirth(string dateOfBirth){
	this->dateOfBirth = dateOfBirth;
}
string employee :: getDateOfBirth(){
	return dateOfBirth;
}

void employee :: setPhoneNumber (string phoneNumber){
	this->phoneNumber = phoneNumber;
}
string employee :: getPhoneNumber (){
	return phoneNumber;
}

void employee :: setSpecialization (string specialization){
	this->specialization = specialization;
}
string employee :: getSpecialization(){
	return specialization;
}

void employee :: setAreaId (string areaId){
	this->areaId = areaId;
}
string employee :: getAreaId(){
	return areaId;
}

void employee :: setLevel(int level){
	this->level = level;
	updateSalary(); // Tu dong tinh lai luong ngay khi dat/doi cap bac
}
int employee :: getLevel(){
	return level;
}

// luong co ban 8m VND nhan he so theo cap bac
void employee :: updateSalary(){
	double factor = 1.0;
	if (this->level == 1) factor = 1.0;
	else if (this->level == 2) factor = 1.4;
	else if (this->level == 3) factor = 1.8;
	this->salary = 8000000 * factor;
}

void employee :: setSalary(double salary){
	this->salary = salary;
} 
double employee :: getSalary(){
	return salary;
}

void employee::inputFromKeyboard(){	
	string temp;
	while (true) {
        cout << "Nhap ho va ten nhan vien (nhap 0 de quay lai): ";
        getline(cin, temp);
        
		if (temp == "0") return;
        
		if (isValidName(temp)){
            setFullName(temp);
            break;
        }
        cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
    }
	
	while (true){
		cout << "Nhap ngay sinh (dd/mm/yyyy)(nhap 0 de quay lai): ";
		getline(cin, temp);
		
		if (temp == "0") return;
		
		if (isValidDate(temp)){
			setDateOfBirth(temp);
			break;
		}
		cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
	}

	bool validSpec = false;
    while (!validSpec) {
        cout << "Chon chuyen mon cua nhan vien:\n";
        cout << "  1. Ky thuat thiet bi (Lap dat, sua chua & bao tri thiet bi cua khach hang)\n";
        cout << "  2. Quan ly truc cap (Quan ly cap quang, bao tri tu cap)\n";
        cout << "  3. Quan tri mang (Van hanh he thong)\n";
        cout << "  0. Quay lai\n";
        cout << "Chon (0-3): ";
        getline(cin, temp);
		
		if (temp == "0") return;
		
        if (temp == "1") {
            setSpecialization("Ky thuat thiet bi");
            validSpec = true;
        } else if (temp == "2") {
            setSpecialization("Quan ly truc cap");
            validSpec = true;
        } else if (temp == "3") {
            setSpecialization("Quan tri mang");
            validSpec = true;
        } else {
            cout << "=> Loi: Lua chon khong hop le! Vui long chi nhap so tu 1 den 3.\n";
        }
    }
	
	bool validLevel = false;
	while (!validLevel) {
        cout << "Chon cap bac cua nhan vien (Luong co ban: 8,000,000 VND):\n";
        cout << "  1. Bac 1 (He so 1.0 ->  8,000,000 VND)\n";
        cout << "  2. Bac 2 (He so 1.4 -> 11,200,000 VND)\n";
        cout << "  3. Bac 3 (He so 1.8 -> 14,400,000 VND)\n";
        cout << "  0. Quay lai\n";
        cout << "Chon (0-3): ";
        getline(cin, temp);
        
        if (temp == "0") return;
        
        if (temp == "1") {
            setLevel(1);
            validLevel = true;
        } else if (temp == "2") {
            setLevel(2);
            validLevel = true;
        } else if (temp == "3") {
            setLevel(3);
            validLevel = true;
        } else {
            cout << "=> Loi: Lua chon khong hop le! Vui long chi nhap so tu 1 den 3.\n";
        }
    }
}

void employee::showToConsole() {
    showToConsole("Chua ro", "Chua ro");
}

void employee::showToConsole(string districtName, string stationName) {
    cout << left << setw(8)  << getId() << "| "
         << left << setw(20) << fullName << "| "
         << left << setw(12) << dateOfBirth << "| "
         << left << setw(12) << phoneNumber << "| "
         << left << setw(20) << specialization << "| "
         << left << setw(8)  << areaId << "| "
         << left << setw(15) << districtName << "| "
         << left << setw(15) << stationName << "| "
         << left << setw(8)  << ("Bac " + to_string(level)) << "| "
         << fixed << setprecision(0) << salary << endl;
}

string employee::toFileString(){
	stringstream ss;
	ss << getId() << "|" << fullName << "|" << dateOfBirth << "|" << phoneNumber << "|" 
	   << specialization << "|" << areaId << "|" 
	   << level << "|" 
	   << fixed << setprecision(0) << salary;
	return ss.str();

}

void employee::fromFileString(string &s){
	if (s.empty()) return;
	stringstream ss(s);
	string tmp;
	getline(ss, tmp, '|');
	setId(tmp);
	
	getline(ss, fullName, '|');
	
	getline(ss, dateOfBirth, '|');
	
	getline(ss, phoneNumber, '|');
	
	getline(ss, specialization, '|');
	
	getline(ss, areaId, '|');
	
	getline(ss, tmp, '|');
	if (!tmp.empty()){
		level = stoi(tmp);
	}
	
	getline(ss, tmp);
	if (!tmp.empty()){
		salary = stod(tmp);
	}
}
