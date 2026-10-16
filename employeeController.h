#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "employee.h"
#include "district.h"
//#include "warranty.h"
#include "repository.h"

using namespace std;

class employeeController {
private:
    Repository<employee> employeeRepo;
    Repository<district> districtRepo;
//    repository<warranty> warrantyRepo;

    void createFunction();
    void readFunction();
    void updateFunction();
    void deleteFunction();

public:
   
    employeeController();
    
    void run();
};
