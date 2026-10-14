#pragma once
#include <iostream>
#include "Repository.h"
#include "internet.h"

using namespace std;

class internetController{
private:
	Repository<internet> internetRepo{"data/internet.txt"};
	
	void createFunction();
	void readFunction();
	void updateFunction();
	void deleteFunction();
public:
	internetController();
	void run();
};


