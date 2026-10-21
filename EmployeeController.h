#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "employee.h"
#include "district.h"
#include "warranty.h"
#include "repository.h"
#include "installation.h"

using namespace std;

class employeeController {
private:
<<<<<<< Updated upstream:EmployeeController.h
    repository<employee> employeeRepo;
    repository<district> districtRepo;
    repository<warranty> warrantyRepo;
//    repository<installationForm> installFormRepo;
=======
    Repository<employee> employeeRepo;
    Repository<district> districtRepo;
    Repository<warranty> warrantyRepo;
    Repository<installationForm> installFormRepo;
>>>>>>> Stashed changes:employeeController.h

    void createFunction();
    void readFunction();
    void updateFunction();
    void deleteFunction();

public:
   
    employeeController();
    
    void run();
};
