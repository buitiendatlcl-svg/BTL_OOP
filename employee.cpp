#include"employee.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cctype>


using namespace std;


employee :: employee (){
	fullName = "";
	dateOfBirth = "";
	phoneNumber = "";
	specialization = "";
	areaId = "";
	salary = 0.0;
}

string employee :: standardizeName (string name) {
    string result = "";
    bool newWord = true;

    for (char c : name) {
        if (c == ' ') {
            // Ch? thêm 1 kho?ng tr?ng n?u tru?c dó dã có ch? (b? qua kho?ng tr?ng d?u câu)
            if (!result.empty() && result.back() != ' ') {
                result += ' '; 
            }
            newWord = true;
        } else {
            if (newWord) {
                result += toupper(c); // Vi?t hoa ch? cái d?u tiên c?a t?
                newWord = false;
            } else {
                result += tolower(c); // Vi?t thu?ng các ch? cái phía sau
            }
        }
    }
    if (!result.empty() && result.back() == ' ') {
        result.pop_back(); 
    }
    return result;
	}

void employee :: setFullName(string fullName){
	this->fullName = standardizeName(fullName);
}
string employee :: getFullName(){
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
	this->specialization = standardizeName (specialization);
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

void employee :: setSalary(double Salary){
	this->salary = salary;
} 
double employee :: getSalary(){
	return salary;
}

void employee::inputFromKeyboard(){	
	string temp;
	double temp2;
	cout << "Nhap ten: ";
	getline(cin, temp);
	setFullName(temp);
	
	cout << "Nhap ngay sinh: ";
	getline(cin, temp);
	setDateOfBirth(temp);
	
	cout << "Nhap sdt: ";
	getline(cin, temp);
	setPhoneNumber(temp);
	
	cout << "Nhap chuyen mon phu trach: ";
	getline(cin, temp);
	setSpecialization(temp);
	
	cout << "Nhap muc luong (VND/thang): ";
	getline(cin, temp);
	if(!temp.empty()){
		salary = stod(temp);
	}
	else {
		salary = 0.0;
	}
	
}

void employee::showToConsole(){
	cout << getId() << "|" << fullName << "|" << dateOfBirth << "|" << phoneNumber << "|" << specialization << "|" 
		 << areaId << "|"<< fixed << setprecision(0) << salary << endl;
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



































