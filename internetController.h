//Bui Tien Dat - B24DCVT062
#pragma once
#include <iostream>
#include "Repository.h"
#include "internet.h"
#include "contract.h"

using namespace std;

class internetController{
private:
	Repository<internet> internetRepo{"data/internet.txt"};
	Repository<contract> contractRepo{"data/contract.txt"};
	
	void createFunction(); // chuc nang them
	void readFunction(); // chuc nang hien thi
	void updateFunction(); // chuc nang chinh sua
	void deleteFunction(); // chuc nang xoa
public:
	internetController();
	void run();
};


