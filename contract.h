//Bui Tien Dat - B24DCVT062
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
	string feedback;
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
	
	void setFeedback(string feedback);
	string getFeedback();
	
	void inputFromKeyboard(); // lay du lieu tu file
	
	void showToConsole(); // hien thi danh sach ra man hinh
	
	string toFileString(); // luu du lieu dang string vao file
	
	void fromFileString(string &line); // lay du lieu tu file
};

