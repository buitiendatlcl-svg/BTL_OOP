#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "employee.h"
#include "district.h"
#include "warranty.h"
#include "repository.h"

using namespace std;

class employeeController {
private:
<<<<<<< HEAD:employeeController.h
    Repository<employee> employeeRepo;
    Repository<district> districtRepo;
    Repository<warranty> warrantyRepo;
    
=======
    repository<employee> employeeRepo;
    repository<district> districtRepo;
    repository<warranty> warrantyRepo;
//    repository<installationForm> installFormRepo;
>>>>>>> hai:EmployeeController.h

    void createFunction();
    void readFunction();
    void updateFunction();
    void deleteFunction();

public:
    employeeController();
<<<<<<< HEAD:employeeController.h
=======
    
>>>>>>> hai:EmployeeController.h
    void run();
};
