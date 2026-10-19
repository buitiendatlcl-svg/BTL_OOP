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

void Invoice::inputFromKeyboard() {
    cout << "\n--- Nhap chi tiet cuoc hoa don ---" << endl;
    cout << "Nhap thang cuoc (1-12): "; cin >> billingMonth;
    cout << "Nhap nam cuoc: "; cin >> billingYear;
//    cout << "Nhap cuoc goi goc (VND): "; cin >> packageFee;
    cout << "Nhap chiet khau (VND): "; cin >> discount;
    cout << "Nhap phu phi (VND): "; cin >> surcharge;
    cin.ignore();
    
    cout << "Trang thai thanh toan (Paid/Unpaid): ";
    getline(cin, paymentStatus);
    
    // T? Ð?NG TÍNH TOÁN & SINH MÃ NGAY T?I ÐÂY:
    generateInvoiceId();   // T? sinh mã: INV-HD001-M10-Y2026
    calculateTotalAmount(); 
}

void Invoice::showToConsole(){
	cout << left
		<< setw(30) << id
		<< setw(20) << contractId
		<< setw(20) << (to_string(billingMonth) + "/" + to_string(billingYear))
		<< setw(20) << packageFee
		<< setw(20) << discount
		<< setw(20) << surcharge
		<< setw(20) << paymentStatus
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





