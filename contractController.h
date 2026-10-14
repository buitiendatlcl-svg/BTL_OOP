#pragma once
#include <iostream>
#include "Repository.h"
#include "contract.h"
#include "customer.h"
#include "internet.h"
#include "district.h"

using namespace std;

class contractController{
private:
	Repository<contract> contractRepo{"data/contract.txt"};
	Repository<customer> customerRepo{"data/customer.txt"};
	Repository<internet> internetRepo{"data/internet.txt"};
	Repository<district> districtRepo{"data/data_khuvuc.txt"};
	
	void createFunction();
	void readFunction();
	void updateFunction();
	void deleteFunction();
public:
	contractController();
	void run();
};

