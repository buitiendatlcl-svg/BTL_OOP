#pragma once
#include <iostream>
#include "repository.h"
#include "contract.h"
#include "customer.h"
#include "internet.h"
#include "district.h"

using namespace std;

class contractController{
private:
	repository<contract> contractRepo{"data/contract.txt"};
	repository<customer> customerRepo{"data/customer.txt"};
	repository<internet> internetRepo{"data/internet.txt"};
	repository<district> districtRepo{"data/data_tram.txt"};
	
	void createFunction();
	void readFunction();
	void updateFunction();
	void deleteFunction();
public:
	contractController();
	void run();
};

