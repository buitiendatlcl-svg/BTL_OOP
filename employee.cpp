#include"employee.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

employee::employee (){
	fullName = "";
	dateOfBirth = "";
	phoneNumber = "";
	specialization = "";
<<<<<<< HEAD
	specialization = ""; //chuyen mon
=======
>>>>>>> hai
	areaId = "";
	salary = 0.0;
}

<<<<<<< HEAD
string employee::standardizeName(string name){ //chuan hoa ten cho: ten nv, chuyen mon
=======

string employee :: standardizeName (string name) {
>>>>>>> hai
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
<<<<<<< HEAD
=======
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
	for (int i = 0; i < date.size(); i++){
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
        if (pos == salaryStr.size() && sal > 0) {
            return true;
        }
    } catch (...) {
        return false;
    }
    return false;        
>>>>>>> hai
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

void employee :: setSalary(double salary){
	this->salary = salary;
} 
double employee :: getSalary(){
	return salary;
}

void employee::inputFromKeyboard(){	
	string temp;
	while (true) {
        cout << "Nhap ho va ten nhan vien: ";
        getline(cin, temp);
        if (isValidName(temp)){
            setFullName(temp);
            break;
        }
        cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
    }
	
	while (true){
		cout << "Nhap ngay sinh (dd/mm/yyyy): ";
		getline(cin, temp);
		if (isValidDate(temp)){
			setDateOfBirth(temp);
			break;
		}
		cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
	}

	while (true){
		cout << "Nhap sdt (10 so, bat dau bang 0): ";
		getline(cin, temp);
		if (isValidPhoneNumber(temp)){
			setPhoneNumber(temp);
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
        cout << "Chon (1-3): ";
        getline(cin, temp);

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
	
	while (true) {
        cout << "Nhap muc luong (VND): ";
        getline(cin, temp);
        if (isValidSalary(temp)) {
            setSalary(stod(temp)); 
            break;
        }
        cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
    }
	
}

void employee::showToConsole() {
    cout << left << setw(8)  << getId() << "| "
         << left << setw(20) << fullName << "| "
         << left << setw(12) << dateOfBirth << "| "
         << left << setw(12) << phoneNumber << "| "
         << left << setw(20) << specialization << "| "
         << left << setw(8)  << areaId << "| "
         << fixed << setprecision(0) << salary << endl;
}

string employee::toFileString(){
	return getId() + "|" + fullName + "|" + dateOfBirth + "|" + phoneNumber + "|" + specialization + "|" + areaId 
			+ "|" + to_string(salary);
}

void employee::fromFileString(string &s){
	stringstream ss(s);
	string tmp;
	getline(ss, tmp, '|');
	setId(tmp);
	
	getline(ss, fullName, '|');
	
	getline(ss, dateOfBirth, '|');
	
	getline(ss, phoneNumber, '|');
	
	getline(ss, specialization, '|');
	
	getline(ss, areaId, '|');
	
	getline(ss, tmp);
	if (!tmp.empty()){
		salary = stod(tmp);
	}
}
<<<<<<< HEAD

=======
>>>>>>> hai
