#pragma once
#include <iostream>
#include <string>
#include "Customer.h"
#include "Repository.h"
#include "contract.h"

using namespace std;

class CustomerController{
private: 
	Repository<Customer> customerRepo;
	Repository<contract> contractRepo;
	
	void addCustomer();
	void displayAllCustomer();
	void searchCustomer();
	void updateCustomer();
	void deleteCustomer();
	
public: 
	CustomerController();
	void run();
};

	

