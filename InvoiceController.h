#pragma once
#include <iostream> 
#include <string> 
#include <iomanip>	
#include "Invoice.h"
#include "contract.h"
#include "Repository.h"

using namespace std;

class InvoiceController{	

private: 
	Repository<Invoice> invoiceRepo;
	Repository<contract> contractRepo;
	
	void addInvoice();
	void displayAllInvoices();
	void updatePaymentStatus();
	void searchInvoiceByContract();
	void deleteInvoiceByContractId();
public: 
	//Ham khoi tao
	InvoiceController();
	void run();
};
