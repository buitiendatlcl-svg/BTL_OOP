#pragma once
#include "entity.h"
#include <string>

using namespace std;

class warranty : public entity{	
private:
	string contractId;
	string employeeId;
	string receivedDate;
	string issueDescribe;
	string status;
	
public:
	warranty ();
	void setContractId(string contractId);
	string getContractId();
	
	void setEmployeeId(string employeeId);
	string getEmployeeId();
	
	void setReceivedDate(string receivedDate);
	string getReceivedDate();
	
	void setIssueDescribe(string issueDescribe);
	string getIssueDescribe();
	
	void setStatus (string status);
	string getStatus();
	
	void inputFromKeyboard();
	
	void showToConsole();
	
	string toFileString();
	
	void fromFileString(string &line);
	
};


