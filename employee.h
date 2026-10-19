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
	double salary;   
    string standardizeName(string name);

public:

    employee();
    
    bool isValidName(string name);
    bool isValidDate(string date);
    bool isValidPhoneNumber (string phoneNumber);
    bool isValidSalary (string salaryStr);

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
    
    void setSalary(double salary);
    double getSalary();

  
	void inputFromKeyboard();
	
	void showToConsole();
	
	string toFileString();
	
	void fromFileString(string &line);

};
