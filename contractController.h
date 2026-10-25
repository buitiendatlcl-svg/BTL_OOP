// UC2 : Bui Tien Dat - giup thuc hien cac thao tac CRUD cho viec quan ly hop dong
#pragma once
#include <iostream>
#include "Repository.h"
#include "contract.h"
#include "customer.h"
#include "internet.h"
#include "district.h"
#include "installation.h"
#include "warranty.h"
#include "invoice.h"
using namespace std;

class contractController{
private:
	Repository<contract> contractRepo{"data/contract.txt"};
	Repository<Customer> customerRepo{"data/customer.txt"};
	Repository<internet> internetRepo{"data/internet.txt"};
	Repository<district> districtRepo{"data/data_khuvuc.txt"};
	Repository<installationForm> installationRepo{"data/data_phieulapdat.txt"};
	Repository<warranty> warrantyRepo{"data/warranty.txt"};
	Repository<Invoice> invoiceRepo{"data/invoice.txt"};
	
	void createFunction();
	void readFunction();
	void updateFunction();
	void deleteFunction();
public:
	contractController();
	void run();
};

