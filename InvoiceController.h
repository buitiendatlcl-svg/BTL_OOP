// Nguyen Manh Khanh - B24DCVT194
#pragma once
#include <iostream> 
#include <string> 
#include <iomanip>	
#include "Invoice.h"
#include "contract.h"
#include "Repository.h"
#include "internet.h"
#include "installation.h"
#include "district.h"
using namespace std;

class InvoiceController{	

private: 
	Repository<Invoice> invoiceRepo;
	Repository<contract> contractRepo;
	Repository<internet> internetRepo;
	Repository<installationForm> installationRepo; // Quan ly phieu lap dat de kiem tra nghiem thu
	Repository<district> districtRepo;             // Quan ly khu vuc / tram quan ly
	
	Invoice* getLastInvoice(string contractId);
	string getInstallationDate(string contractId);
	void autoUpdateOverdueStatus();
	
	void addInvoice();
	void displayAllInvoices();
	void updatePaymentStatus();
	void deleteInvoiceByContractId();
public: 
	//Ham khoi tao
	InvoiceController();
	void run();
};
