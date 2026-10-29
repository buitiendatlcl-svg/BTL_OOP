// Nguyen Manh Khanh - B24DCVT194
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include "Customer.h"
#include "Repository.h"
#include "contract.h"
using namespace std;

class CustomerController{
private: 
	Repository<Customer> customerRepo;
	Repository<contract> contractRepo;
	
	//Ham hien thi danh sach tinh va cho nguoi dung chon dia chi
	string selectAddress();
	
	bool isNationalIdDuplicate(string cccd, string excludeId = "");
    bool isPhoneNumberDuplicate(string sdt, string excludeId = "");
	
	void addCustomer();
	void displayAllCustomer();
	void updateCustomer();
	void deleteCustomer();
	
public: 
	CustomerController();
	void run();
	
	static vector<string> getListProvinces();
};

	

