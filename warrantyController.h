#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "warranty.h"
#include "employee.h"
#include "contract.h"
#include "installation.h"
#include "repository.h"

class warrantyController {
private:
	Repository <warranty> warrantyRepo;
	Repository <contract> contractRepo;
	Repository <employee> employeeRepo;
	Repository <installationForm> installFormRepo;

	// Moi hop dong chi co 1 phieu lap dat -> Tim phieu lap dat theo Ma Hop Dong
	installationForm* getInstallFormByContractId(string contractId);
	
	void createFunction();
	void readFunction();
	void updateFunction();
	void deleteFunction();

public:
	warrantyController();
	void run();
};
