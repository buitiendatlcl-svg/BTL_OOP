#include "Invoice.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

Invoice::Invoice(){
	id = "";
	contractId = "";
	billingMonth = 0;
	billingYear = 0;
	packageFee = 0.0;
	discount = 0.0;
	surcharge = 0.0;
	totalAmount = 0.0;
	paymentStatus = "Unpaid";
	
}

Invoice::Invoice(string contractId, int billingMonth, int billingYear, double packageFee, double discount, double surcharge, double totalAmount,
				string paymentStatus){
		this->contractId = contractId;
		this->billingMonth = billingMonth;
		this->billingYear = billingYear;
		this->packageFee = packageFee;
		this->discount = discount;
		this->surcharge = surcharge;
		this->totalAmount = totalAmount;
		this->paymentStatus = paymentStatus;
		
		generateInvoiceId();
		calculateTotalAmount();
		
	}
	
//Ham sinh Id hoa don

void Invoice::generateInvoiceId(){
	string monthStr;
	if(billingMonth < 10){
		monthStr = "0" + to_string(billingMonth);
	}
	else{
		monthStr = to_string(billingMonth);
	}
	
	id = "INV-" + contractId + "-M" + monthStr + "-Y" + to_string(billingYear);
	
}
//Ham tinh tong tien

void Invoice::calculateTotalAmount(){
	totalAmount = packageFee - discount + surcharge;
	if(totalAmount < 0){
		totalAmount = 0.0;
	}
}
	
void Invoice::setContractId( string& contractId){
	this->contractId = contractId;
}
string Invoice::getContractId() {
	return contractId;
}

void Invoice::setBillingMonth(int billingMonth){
	this->billingMonth = billingMonth;
}
int Invoice::getBillingMonth() {
	return billingMonth;
}

void Invoice::setBillingYear(int billingYear){
	this->billingYear = billingYear;
}
int Invoice::getBillingYear() {
	return billingYear;
}

void Invoice::setPackageFee(double packageFee){
	this->packageFee = packageFee;
}
double Invoice::getPackageFee() {
	return packageFee;
}

void Invoice::setDiscount(double discount){
	this->discount = discount;
}
double Invoice::getDiscount() {
	return discount;
}

void Invoice::setSurcharge(double surcharge){
	this->surcharge = surcharge;
}
double Invoice::getSurcharge() {
	return surcharge;
}

double Invoice::getTotalAmount() {
	return totalAmount;
}

string Invoice::getPaymentStatus(){
	return paymentStatus;
}
void Invoice::setPaymentStatus(const string& paymentStatus){
	this->paymentStatus = paymentStatus;
}

//Kiem tra thang phai la so > 0, < 13
bool Invoice::isValidBillingMonth(string billingMonthStr){
	if(billingMonthStr.empty()) return false;
	try{
		size_t pos;
		int month = stoi(billingMonthStr, &pos);
		if(pos == billingMonthStr.size() && month >0 && month < 13){
			return true;
		}
	}
	catch(...){
		return false;
	}
}

// Kiem tra nam phai la so lon hon 0
bool Invoice::isValidBillingYear(string billingYearStr){
	if(billingYearStr.empty()) return false;
	try{
		size_t pos;
		int year = stoi(billingYearStr, &pos);
		if(pos == billingYearStr.size() && year > 2025 ){
			return true;
		}
	}
	catch(...){
		return false;
	}
}
		
bool Invoice::isValidDiscount(string discountStr){
	if(discountStr.empty()) return false;
	try{
		size_t pos;
		double dis = stod(discountStr, &pos);
		if(pos == discountStr.size() && dis > 0){
			return true;
		}
	}
	catch(...){
		return false;
	}
}

bool Invoice::isValidSurcharge(string surchargeStr){
	if(surchargeStr.empty()) return false;
	try{
		size_t pos;
		double surcharge = stod(surchargeStr, &pos);
		if(pos == surchargeStr.size() && surcharge > 0){
			return true;
		}
	}
	catch(...){
		return false;
	}
}

void Invoice::inputFromKeyboard() {
	string temp;
    cout << "\n--- Nhap chi tiet cuoc hoa don ---" << endl;
//    cout << "Nhap thang cuoc (1-12): "; cin >> billingMonth;
	while(true){
		cout << "\nNhap thang cuoc (1-12) (Nhap '0' de quay lai): "; 
		getline(cin, temp);
		
		if(temp == "0"){
			billingMonth = 0;
			return;
		}
		
		if(isValidBillingMonth(temp)){
			setBillingMonth(stoi(temp));
			break;
		}
		cout << "\n[LUU Y]: Vui long nhap lai thang cuoc !" << endl;
	}
	
//    cout << "Nhap nam cuoc: "; cin >> billingYear;
	while(true){
		cout << "\nNhap nam cuoc (Nhap '0' de quay lai): "; 
		getline(cin, temp);
		
		if(temp == "0"){
			billingYear = 0;
			return;
		}
		
		if(isValidBillingYear(temp)){
			setBillingYear(stoi(temp));
			break;
		}
		cout << "\n[LUU Y]: Vui long nhap lai nam cuoc !" << endl;
	}
	
//    cout << "Nhap chiet khau (VND): "; cin >> discount;
	while(true){
		cout << "\nNhap chiet khau (VND) (Nhap '-1' de quay lai): ";
		getline(cin, temp);
		
		if(temp == "-1"){
			discount = -1;
			return;
		}
		
		if(isValidDiscount(temp)){
			setDiscount(stod(temp));
			break;
		}
		cout << "\[LUU Y]: Vui long nhap lai chiet khau !" << endl;
	}
	
//    cout << "Nhap phu phi (VND): "; cin >> surcharge;
	while(true){
		cout << "\nNhap phu phi (VND) (Nhap '-1' de quay lai): ";
		getline(cin, temp);
		
		if(temp == "-1"){
			surcharge = -1;
			return;
		}
		
		if(isValidSurcharge(temp)){
			setSurcharge(stod(temp));
			break;
		}
		cout << "\[LUU Y]: Vui long nhap lai phu phi !" << endl;
	}
	
	//Unpaid / paid
	while(true){
    cout << "\n[CAC LUA CHON DE CAP NHAT TRANG THAI THANH TOAN]";
    cout << "\n'1' - Paid";
    cout << "\n'2' - Unpaid";
    cout << "\n'0' - Quay tro lai menu";
    cout << "\nNhap lua chon cua ban: ";
    string choice;
    getline(cin, choice);
    if(choice == "1"){ setPaymentStatus("Paid"); break; }
    else if(choice == "2"){setPaymentStatus("Unpaid"); break; }
    else if(choice == "0"){paymentStatus = ""; return; }
    else{
    	cout << "[LOI]: Vui long chi chon 0, 1 hoac 2!" << endl;
	}
}
    
    // T? Ð?NG TÍNH TOÁN & SINH MÃ NGAY T?I ÐÂY:
    generateInvoiceId();   // T? sinh mã: INV-HD001-M10-Y2026
    calculateTotalAmount(); 
}

void Invoice::showToConsole(){
	cout << left
		<< setw(30) << id
		<< setw(20) << contractId
		<< setw(20) << (to_string(billingMonth) + "/" + to_string(billingYear))
		<< setw(15) << packageFee
		<< setw(15) << discount
		<< setw(15) << surcharge
		<< setw(15) << totalAmount
		<< setw(15) << paymentStatus
		<< endl;
}

// Ghi file
string Invoice::toFileString()  {
    return id + "|" + contractId + "|" + to_string(billingMonth) + "|" + to_string(billingYear) + "|" 
         + to_string(packageFee) + "|" + to_string(discount) + "|" + to_string(surcharge) + "|" 
         + to_string(totalAmount) + "|" + paymentStatus;
}
// 9 Doc file
void Invoice::fromFileString( string& line) {
    if (line.empty()) return;
    stringstream ss(line);
    string item;
    getline(ss, id, '|'); 
    getline(ss, contractId, '|');
    
    getline(ss, item, '|'); if (!item.empty()) billingMonth = stoi(item);
    getline(ss, item, '|'); if (!item.empty()) billingYear = stoi(item);
    getline(ss, item, '|'); if (!item.empty()) packageFee = stod(item);
    getline(ss, item, '|'); if (!item.empty()) discount = stod(item);
    getline(ss, item, '|'); if (!item.empty()) surcharge = stod(item);
    getline(ss, item, '|'); if (!item.empty()) totalAmount = stod(item);
    
    getline(ss, paymentStatus, '|');
}





