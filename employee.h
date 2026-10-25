//Tran Hoang Hai - MSV: B24DCVT123
#pragma once
#include "entity.h"
#include <string>

using namespace std;

class employee : public entity {
private:
    string fullName;
    string dateOfBirth;
    string phoneNumber;
    string specialization; 
    string areaId;
    int level;     // Cap bac: 1, 2, 3
    double salary;   
    string standardizeName(string fullName);

public:

    employee();
    
    bool isValidName(string name);
    bool isValidDate(string date);
    bool isValidPhoneNumber(string phoneNumber);
    bool isValidSalary(string salaryStr);

    void setFullName(string fullName);
    string getFullName();
    
    void setDateOfBirth(string dateOfBirth);
    string getDateOfBirth();
    
    void setPhoneNumber(string phoneNumber);
    string getPhoneNumber();
    
    void setSpecialization(string specialization);
    string getSpecialization();
	
    void setAreaId(string areaId);
    string getAreaId();
    
    void setLevel(int level);
    int getLevel();
    void updateSalary();

    void setSalary(double salary);
    double getSalary();

    void inputFromKeyboard();
	
    void showToConsole();
    void showToConsole(string districtName, string stationName);
	
    string toFileString();
	
    void fromFileString(string &line);

};
