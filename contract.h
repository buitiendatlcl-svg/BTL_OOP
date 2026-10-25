// UC2 : Bui Tien Dat - Quan ly hop dong dich vu
#pragma once
#include "entity.h"
#include <string>
using namespace std;

class contract : public entity{
private:
	string customerId, packageId, areaId, signDate;
	int term;
	int status;
	string expiryDate;
public:
	contract();
	
	void setCustomerId(string customerId);
	string getCustomerId();
	
	void setPackageId(string packageId);
	string getPackageId();
	
	void setAreaId(string areaId);
	string getAreaId();
	
	void setSignDate(string signDate);
	string getSignDate();
	
	void setTerm(int term);
	int getTerm();
	
	void setStatus(int status);
	int getStatus();
	void setExpiryDate(string expiryDate);
	string getExpiryDate();
	void calculateExpiryDate(string installDate);
	
	void inputFromKeyboard();
	
	void showToConsole();
	
	string toFileString();
	
	void fromFileString(string &line);
};

