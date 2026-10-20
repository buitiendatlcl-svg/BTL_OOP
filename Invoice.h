
#pragma once
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
		
	public : 
		// Ham khoi tao
		
		//Neu theo cach Invoice2 khong can truyen tham so cua string Id;
		Invoice(string contractId, int billingMonth, int billingYear, double packageFee, double discount, double surcharge, double totalAmount
		,string paymentStatus);	

		Invoice(); 
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
		

		bool isValidBillingMonth(string billingMonthStr);
		bool isValidBillingYear(string billingYearStr);
		bool isValidDiscount(string discountStr);
		bool isValidSurcharge(string surchargeStr);
		

		void inputFromKeyboard() override;
		void showToConsole()override;
		string toFileString() override;
		void fromFileString(string& line) override;	
};
