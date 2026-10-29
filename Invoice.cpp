// Nguyen Manh Khanh - B24DCVT192
#include "Invoice.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>
#include <algorithm>

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
	invoiceDate = "";
	dueDate = "";
	paymentDate = "none";	
}

Invoice::Invoice(string contractId, int billingMonth, int billingYear, double packageFee, double discount, double surcharge, double totalAmount,
				string paymentStatus, string invoiceDate, string dueDate, string paymentDate){
	this->contractId = contractId;
	this->billingMonth = billingMonth;
	this->billingYear = billingYear;
	this->packageFee = packageFee;
	this->discount = discount;
	this->surcharge = surcharge;
	this->totalAmount = totalAmount;
	this->paymentStatus = paymentStatus;
	this->invoiceDate = invoiceDate;
	this->dueDate = dueDate;
	this->paymentDate = paymentDate;
	
	generateInvoiceId();
	calculateTotalAmount();
}
	
//Ham sinh Id hoa don

void Invoice::generateInvoiceId() {
    string cleanDate = invoiceDate;
    cleanDate.erase(remove(cleanDate.begin(), cleanDate.end(), '/'), cleanDate.end());
    id = "INV-" + contractId + "-" + cleanDate;
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

string Invoice::getInvoiceDate() {
	return invoiceDate;
}
void Invoice::setInvoiceDate(string invoiceDate) {
	this->invoiceDate = invoiceDate;
}

string Invoice::getDueDate() {
	return dueDate;
}
void Invoice::setDueDate(string dueDate) {
	this->dueDate = dueDate;
}

string Invoice::getPaymentDate() {
	return paymentDate;
}
void Invoice::setPaymentDate(string paymentDate) {
	this->paymentDate = paymentDate;
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
	catch(...) {
		return false;
	}
	return false;
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
	catch(...) {
		return false;
	}
	return false;
}
// Kiem tra chiet khau (cho phep >= 0 de nhap 0 VND khi khong co giam gia)
bool Invoice::isValidDiscount(string discountStr){
	if(discountStr.empty()) return false;
	try{
		size_t pos;
		double dis = stod(discountStr, &pos);
		if(pos == discountStr.size() && dis >= 0){
			return true;
		}
	}
	catch(...){
		return false;
	}
	return false;
}

// Kiem tra phu phi (cho phep >= 0 de nhap 0 VND khi khong co phat/no)
bool Invoice::isValidSurcharge(string surchargeStr){
	if(surchargeStr.empty()) return false;
	try{
		size_t pos;
		double surcharge = stod(surchargeStr, &pos);
		if(pos == surchargeStr.size() && surcharge >= 0){
			return true;
		}
	}
	catch(...){
		return false;
	}
	return false;
}

// Kiem tra dinh dang ngay dd/mm/yyyy
bool Invoice::isValidDate(string dateStr){
	if(dateStr.empty()) return false;
	stringstream ss(dateStr);
	int d, m, y;
	char c1, c2;
	if (ss >> d >> c1 >> m >> c2 >> y) {
		if (c1 == '/' && c2 == '/' && d >= 1 && d <= 31 && m >= 1 && m <= 12 && y >= 2000) {
			return true;
		}
	}
	return false;
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
	
// Tu dong thiet lap ngay lap hoa don va han thanh toan theo thang/nam cuoc
	string mStr = (billingMonth < 10) ? ("0" + to_string(billingMonth)) : to_string(billingMonth);
	cout << "\nNhap ngay lap hoa don (Nhan Enter lay mac dinh '01/" << mStr << "/" << billingYear << "'): ";
	getline(cin, temp);
	if (temp.empty() || !isValidDate(temp)) {
		setInvoiceDate("01/" + mStr + "/" + to_string(billingYear));
	} else {
		setInvoiceDate(temp);
	}
	cout << "Nhap han thanh toan (Nhan Enter lay mac dinh '15/" << mStr << "/" << billingYear << "'): ";
	getline(cin, temp);
	if (temp.empty() || !isValidDate(temp)) {
		setDueDate("15/" + mStr + "/" + to_string(billingYear));
	} else {
		setDueDate(temp);
	}
	
	// Mac dinh hoa don moi lap luon o trang thai chua thanh toan (Unpaid)
	setPaymentStatus("Unpaid");
	setPaymentDate("none");	
	// Tu dong tinh toan ma va tong tien
	generateInvoiceId();
	calculateTotalAmount(); 
}

void Invoice::showToConsole(){
	cout << left
		<< setw(20) << id
		<< "| " << setw(8)  << contractId
		<< "| " << setw(12) << fixed << setprecision(0) << packageFee
		<< "| " << setw(12) << fixed << setprecision(0) << discount
		<< "| " << setw(12) << fixed << setprecision(0) << surcharge
		<< "| " << setw(13) << fixed << setprecision(0) << totalAmount
		<< "| " << setw(12) << paymentStatus
		<< "| " << setw(13) << invoiceDate
		<< "| " << setw(13) << dueDate
		<< "| " << setw(12) << paymentDate
		<< endl;
}
// Ghi 13 cot ra file
string Invoice::toFileString()  {
    return id + "|" + contractId + "|" + to_string(billingMonth) + "|" + to_string(billingYear) + "|" 
         + to_string(packageFee) + "|" + to_string(discount) + "|" + to_string(surcharge) + "|" 
         + to_string(totalAmount) + "|" + paymentStatus + "|" + invoiceDate + "|" + dueDate + "|"
         + paymentDate;
}
// Doc 13 cot tu file va tu dong xu ly tuong thich du lieu cu
void Invoice::fromFileString(string& line) {
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
    getline(ss, invoiceDate, '|');
    getline(ss, dueDate, '|');
    getline(ss, paymentDate, '|');
	if (!paymentStatus.empty() && paymentStatus.back() == '\r') paymentStatus.pop_back();
	// Tu dong gan mac dinh neu doc file cu (khi chua co 4 cot moi)
	string mStr = (billingMonth < 10) ? ("0" + to_string(billingMonth)) : to_string(billingMonth);
	if (invoiceDate.empty()) invoiceDate = "01/" + mStr + "/" + to_string(billingYear);
	if (dueDate.empty()) dueDate = "15/" + mStr + "/" + to_string(billingYear);
	if (paymentDate.empty()) paymentDate = (paymentStatus == "Paid") ? invoiceDate : "none";
}

bool Invoice::parseDate(const string& str, int& d, int& m, int& y) {
    if (str.empty()) return false;
    stringstream ss(str);
    char c1, c2;
    if (ss >> d >> c1 >> m >> c2 >> y) {
        if (c1 == '/' && c2 == '/' && d >= 1 && d <= 31 && m >= 1 && m <= 12 && y >= 2000) {
            return true;
        }
    }
    return false;
}
string Invoice::formatDate(int d, int m, int y) {
    stringstream ss;
    ss << setfill('0') << setw(2) << d << "/"
       << setw(2) << m << "/"
       << setw(4) << y;
    return ss.str();
}
int Invoice::dateToNumber(const string& dateStr) {
    int d = 0, m = 0, y = 0;
    if (parseDate(dateStr, d, m, y)) {
        return y * 10000 + m * 100 + d;
    }
    return 0;
}
bool Invoice::compareDate(const string& d1, const string& d2) {
    return dateToNumber(d1) < dateToNumber(d2);
}
string Invoice::addMonthsToDate(const string& dateStr, int months) {
    int d = 0, m = 0, y = 0;
    if (!parseDate(dateStr, d, m, y)) return dateStr;
    m += months;
    while (m > 12) {
        m -= 12;
        y += 1;
    }
    while (m < 1) {
        m += 12;
        y -= 1;
    }
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    if (isLeap) daysInMonth[2] = 29;
    if (d > daysInMonth[m]) {
        d = daysInMonth[m];
    }
    return formatDate(d, m, y);
}
string Invoice::getCurrentDate() {
    time_t t = time(0);
    tm* now = localtime(&t);
    return formatDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}




