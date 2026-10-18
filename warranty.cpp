#include"warranty.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

warranty :: warranty (){
	contractId = "";
	employeeId = "";
	receivedDate = "";
	issueDescribe = "";
	status = "";
}
	void warranty :: setContractId (string contractId){
		this -> contractId = contractId;
	}	
	string warranty :: getContractId(){
		return contractId;
	}
	
	void warranty :: setEmployeeId (string employeeId){
		this -> employeeId = employeeId;
	}
	string warranty :: getEmployeeId (){
		return employeeId;
	}
	
	void warranty :: setReceivedDate (string receivedDate){
		this -> receivedDate = receivedDate;
	}
	string warranty :: getReceivedDate (){
		return receivedDate;
	}
	
	void warranty :: setIssueDescribe (string issueDescribe){
		this -> issueDescribe = issueDescribe;
	}
	string warranty :: getIssueDescribe (){
		return issueDescribe;
	}

	void warranty :: setStatus (string status){
		this -> status = status;
	}
	string warranty :: getStatus (){
		return status;
	}	
	
	
	void warranty :: inputFromKeyboard(){
		string temp;		
		cout << "Nhap ngay tiep nhan: " << endl;
		getline (cin, temp);
		setReceivedDate(temp);
		
		cout << "Nhap noi dung su co : " << endl;
		getline (cin, temp);
		setIssueDescribe (temp);
		
		bool validStatus = false;
    	while (!validStatus) {
        cout << "Chon trang thai xu ly:\n";
        cout << "1. Cho xu ly\n";
        cout << "2. Dang sua chua\n";
        cout << "3. Da hoan thanh\n";
        cout << "4. Da huy\n";
        cout << "Chon (1-4): ";
        
        getline(cin, temp);

        if (temp == "1") {
            setStatus("Cho xu ly");
            validStatus = true;
        } else if (temp == "2") {
            setStatus("Dang sua chua");
            validStatus = true;
        } else if (temp == "3") {
            setStatus("Da hoan thanh");
            validStatus = true;
        } else if (temp == "4") {
            setStatus("Da huy");
            validStatus = true;
        } else {
            cout << "=> Lua chon khong hop le! Vui long chon tu 1 den 4.\n";
        }		
	}
}

void warranty::showToConsole(){
	cout << getId() << "|" << contractId << "|" << employeeId << "|" << receivedDate << "|" << issueDescribe << "|" << status << endl;
}

string warranty::toFileString(){
	return getId() + "|" + contractId + "|" + employeeId + "|" + receivedDate + "|" + issueDescribe + "|" + status;
}

void warranty::fromFileString(string &s){
	stringstream ss(s);
	string tmp;
	getline(ss, tmp, '|');
	setId(tmp);
	
	getline(ss, contractId, '|');
	
	getline(ss, employeeId, '|');
	
	getline(ss, receivedDate, '|');
	
	getline(ss, issueDescribe, '|');
	
	getline(ss, status, '|');
}
