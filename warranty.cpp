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

bool warranty::isValidDate(string date){ //check dinh dang dd/mm/yyyy
	if (date.size() != 10 || date[2] != '/' || date[5] != '/') return false;
	for (int i = 0; i < date.size(); i++){
		if (i == 2 || i == 5) continue; // neu la dau "/" thi bo qua
		if (!isdigit(date[i])) return false;
	}
	
	int d = stoi(date.substr(0, 2)); 
	int m = stoi(date.substr(3, 2));
	int y = stoi(date.substr(6, 4));
	
	if ( d < 1 || m < 1 || m > 12 || y < 2000 || y > 2026 ) return false;
	
	int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29; // nam nhuan
    }
    return d <= daysInMonth[m]; // so sanh ngay nhap & ngay toi da cua thang do, neu dung tra ve true	
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

	while (true){
		cout << "Nhap ngay tiep nhan : ";
		getline (cin, temp);
		if (isValidDate(temp)){
			setReceivedDate(temp);
			break;
		}
		cout << "=> Loi! Sai dinh dang, vui long nhap lai!" << endl;
	}
	
	bool validIssue = false;
    while (!validIssue) {
    cout << "Chon noi dung su co:\n";
    cout << "  1. Mat ket noi Internet (Dut cap, den LOS do)\n";
    cout << "  2. Mang cham, chap chon (Suy hao tin hieu)\n";
    cout << "  3. Loi thiet bi Modem/Wifi (Hong nguon, loi phat song)\n";
    cout << "  4. Van de khac\n";
    cout << "Chon (1-4): ";
    
    getline(cin, temp);

    if (temp == "1") {
        setIssueDescribe("Mat ket noi Internet");
        validIssue = true;
    } else if (temp == "2") {
        setIssueDescribe("Mang cham, chap chon");
        validIssue = true;
    } else if (temp == "3") {
        setIssueDescribe("Loi thiet bi Modem/Wifi");
        validIssue = true;
    } else if (temp == "4") {
        setIssueDescribe("Van de khac");
        validIssue = true;
    } else {
        cout << "=> Loi: Lua chon khong hop le! Vui long chon tu 1 den 4.\n";
    }
    }
	
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

void warranty::showToConsole() {
    cout << left << setw(8)  << getId() << "| "
         << left << setw(10) << contractId << "| "
         << left << setw(10) << employeeId << "| "
         << left << setw(12) << receivedDate << "| "
         << left << setw(28) << issueDescribe << "| "
         << status << endl;
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
