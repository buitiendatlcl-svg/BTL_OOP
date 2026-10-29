// Nguyen Manh Khanh - B24DCVT192
#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
using namespace std;

class Invoice : public entity{
	private : 
		// Id cua hoa don(InvoiceId) lay tu Id cua lop cha Entity.h
		string contractId; // lien ket khoa ngoai voi HopDong cua Dat09
		int billingMonth;
		int billingYear;
		double packageFee;
		double discount;
		double surcharge; //phu phi (VD: no tien tu thang truoc)
		double totalAmount; // tong chi phi
		string paymentStatus;
		
		string invoiceDate;   // Ngay lap hoa don (dd/mm/yyyy)
		string dueDate;       // Han thanh toan (dd/mm/yyyy)
		string paymentDate;   // Ngay khach tra tien thuc te (dd/mm/yyyy hoac "none")		
	public : 
		// Ham khoi tao
		Invoice();
		Invoice(string contractId, int billingMonth, int billingYear, double packageFee, double discount, double surcharge, double totalAmount,
        	string paymentStatus, string invoiceDate = "", string dueDate = "", string paymentDate = "none");
	    Invoice(string contractId, double packageFee, double discount, double surcharge,
	            double totalAmount, string paymentStatus, string invoiceDate, string dueDate, string paymentDate = "none");

		void generateInvoiceId();
		
		string getContractId() ;
		void setContractId(string& contractId);
		
		int getBillingMonth() ;
		void setBillingMonth(int billingMonth);
		
		int getBillingYear() ;
		void setBillingYear(int billingYear);
		
		double getPackageFee() ;
		void setPackageFee(double packageFee);
		
		double getDiscount() ;
		void setDiscount(double discount);
		
		double getSurcharge() ;
		void setSurcharge(double surcharge);
		
		double getTotalAmount() ; // Ham tinh tong ko can Setter
		
		void calculateTotalAmount(); // Cong thuc totalAmount = packageFee - discount(%)*packageFee + surcharge
		
		string getPaymentStatus() ;
		void setPaymentStatus(const string& paymentStatus); // ham Getter/Setter khi cap nhat thanh toan 
		
		string getInvoiceDate();
		void setInvoiceDate(string invoiceDate);
		
		string getDueDate();
		void setDueDate(string dueDate);
		
		string getPaymentDate();
		void setPaymentDate(string paymentDate);
		
		static bool parseDate(const string& str, int& d, int& m, int& y);
		static string formatDate(int d, int m, int y);
		static int dateToNumber(const string& dateStr); 
		static bool compareDate(const string& d1, const string& d2); 
		static string addMonthsToDate(const string& dateStr, int months);
		static string getCurrentDate(); 
		
		bool isValidBillingMonth(string billingMonthStr);
		bool isValidBillingYear(string billingYearStr);
		bool isValidDiscount(string discountStr);
		bool isValidSurcharge(string surchargeStr);
		bool isValidDate(string dateStr); 
		
		void inputFromKeyboard() override;
		void showToConsole() override;
		string toFileString() override;
		void fromFileString(string& line) override;
};
