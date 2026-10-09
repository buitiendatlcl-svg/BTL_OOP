#pragma once
#include <iostream>
#include "repository.h"
#include "internet.h"

using namespace std;

class internetController{
private:
	repository<internet> internetRepo{"data/internet.txt"};
	
	void createFunction();
	void readFunction();
	void updateFunction();
	void deleteFunction();
public:
	internetController();
	void run();
};


