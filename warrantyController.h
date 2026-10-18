#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "warranty.h"
#include "employee.h"
#include "contract.h"
#include "repository.h"

class warrantyController {
private:
	Repository <warranty> warrantyRepo;
	Repository <contract> contractRepo;
	Repository <employee> employeeRepo;
	
	void createFunction();
	void readFunction();
	void updateFunction();
	void deleteFunction();

public:
	warrantyController();
	
	void run();
};
