#pragma once
#include "entity.h"
#include <string>  

using namespace std;

class contract : public entity{
private:
	string customerId, packageId, areaId, signDate;
	int term;
	int status;
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
	
	void inputFromKeyboard();
	
	void showToConsole();
	
	string toFileString();
	
	void fromFileString(string &line);
};
