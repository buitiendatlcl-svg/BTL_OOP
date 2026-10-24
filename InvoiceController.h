#pragma once
#include <iostream> 
#include <string> 
#include <iomanip>	
#include "Invoice.h"
#include "contract.h"
#include "Repository.h"
#include "internet.h"
#include "installation.h"

using namespace std;

class InvoiceController{	

private: 
	Repository<Invoice> invoiceRepo;
	Repository<contract> contractRepo;
	Repository<internet> internetRepo;
	Repository<installationForm> installationRepo; // Quan ly phieu lap dat de kiem tra nghiem thu
	
	// CAC PHUONG THUC MOI THEO DE XUAT
	Invoice* getLastInvoice(string contractId);
	bool isWithinContractPeriod(string contractId, int month, int year);
	void addInvoice();
	void displayAllInvoices();
	void updatePaymentStatus();
	void deleteInvoiceByContractId();
public: 
	//Ham khoi tao
	InvoiceController();
	void run();
};
