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
		repository <warranty> warrantyRepo;
		repository <contract> contractRepo;
		repository <employee> employeeRepo;
		
		void createFunction();
		void readFunction();
		void updateFunction();
		void deleteFunction();
	
	public:
		warrantyController();
		
		void menu();
};
